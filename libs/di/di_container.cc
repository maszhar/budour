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

#include "di_container.h"
#include "session/infrastructure/ports/persistence/session_repository.h"
#include "session/infrastructure/persistence/session_file_storage.h"
#include "session/core/application/session_controller.h"

namespace MYAPP
{
  std::unordered_map<std::type_index, DIContainer::Factory> DIContainer::_factories;
  std::unordered_map<std::type_index, std::shared_ptr<Component>> DIContainer::_instances;

  void DIContainer::initialize()
  {
    register_<SessionRepository>(
        []
        {
          return std::make_shared<SessionFileStorage>();
        });

    register_<SessionController>(
        []
        {
          return std::make_shared<SessionController>(
              resolve<SessionRepository>());
        });
  }
}