/*
 * Copyright (C) 2026 Fikri Mustofa <fikrimustofa024@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>
#include <concepts>
#include "component.h"

namespace MYAPP
{
  class DIContainer
  {
  public:
    static void initialize();

    template <std::derived_from<Component> T>
    static T *resolve()
    {
      static_assert(
          std::is_base_of_v<Component, T>,
          "T must inherit Component.");

      auto key = std::type_index(typeid(T));

      auto instance = _instances.find(key);
      if (instance != _instances.end())
      {
        return static_cast<T *>(instance->second.get());
      }

      auto factory = _factories.find(key);
      if (factory == _factories.end())
      {
        throw std::runtime_error(
            std::string("This component factory is not registered: " + T::class_name));
      }

      auto new_instance = factory->second();
      _instances[key] = new_instance;

      return static_cast<T *>(new_instance.get());
    }

    static void clear()
    {
      _instances.clear();
    }

  private:
    using Factory = std::function<std::shared_ptr<Component>()>;

    template <std::derived_from<Component> T>
    static void register_(std::function<std::shared_ptr<T>()> factory)
    {
      static_assert(
          std::is_base_of_v<Component, T>,
          "T must inherit Component");

      _factories[typeid(T)] = [factory]()
      {
        return std::static_pointer_cast<Component>(factory());
      };
    }

    static std::unordered_map<std::type_index, Factory> _factories;
    static std::unordered_map<std::type_index, std::shared_ptr<Component>> _instances;
  };
}