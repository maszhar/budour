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

#include <memory>
#include "observable_base.h"
#include "observable_state.h"

namespace MYAPP
{
  class Subscription
  {
  public:
    Subscription() = default;

    Subscription(const Subscription &) = delete;
    Subscription &operator=(const Subscription &) = delete;

    Subscription(Subscription &&other) noexcept
    {
      swap(other);
    }

    Subscription &operator=(Subscription &&other) noexcept
    {
      if (this != &other)
      {
        unsubscribe();
        swap(other);
      }

      return *this;
    }

    ~Subscription() noexcept
    {
      unsubscribe();
    }

    void unsubscribe()
    {
      if (_observable == nullptr)
        return;

      if (_state.lock())
      {
        _observable->unsubscribe(_id);
      }

      _observable = nullptr;
      _state.reset();
      _id = 0;
    }

  private:
    template <typename T>
    friend class Observable;

    ObservableBase *_observable = nullptr;
    std::weak_ptr<ObservableState> _state;
    ObservableBase::SubscriptionId _id = 0;

    Subscription(
        ObservableBase *observable,
        std::shared_ptr<ObservableState> state,
        ObservableBase::SubscriptionId id)
        : _observable(observable),
          _state(std::move(state)),
          _id(id)
    {
    }

    void swap(Subscription &other) noexcept
    {
      std::swap(_observable, other._observable);
      std::swap(_state, other._state);
      std::swap(_id, other._id);
    }
  };
}