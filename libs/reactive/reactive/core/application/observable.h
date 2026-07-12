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

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include "observable_base.h"
#include "observable_state.h"
#include "subscription.h"

namespace MYAPP
{
  template <typename T>
  class Observable : public ObservableBase
  {
  public:
    using Callback = std::function<void(const T &)>;

    Observable() = default;

    explicit Observable(const T &value)
        : _value(value)
    {
    }

    Observable(const Observable &) = delete;
    Observable &operator=(const Observable &) = delete;

    Observable(Observable &&) = delete;
    Observable &operator=(Observable &&) = delete;

    virtual ~Observable() = default;

    const T &get() const
    {
      return _value;
    }

    void set(const T &value)
    {
      if (_value == value)
        return;

      _value = value;
      notify();
    }

    Subscription subscribe(Callback callback)
    {
      Observer observer{
          ++_next_subscription_id,
          std::move(callback)};

      if (_notifying)
      {
        _pending_observers.push_back(std::move(observer));
      }
      else
      {
        _observers.push_back(std::move(observer));
      }

      return Subscription{
          this,
          _state,
          observer.id};
    }

    void unsubscribe(SubscriptionId subscription_id) override
    {
      if (_notifying)
      {
        _pending_unsubscribes.push_back(subscription_id);
        return;
      }

      remove_observer(subscription_id);
    }

  protected:
    virtual void notify()
    {
      _notifying = true;

      for (const auto &observer : _observers)
      {
        observer.callback(_value);
      }

      _notifying = false;

      process_pending_subscribes();
      process_pending_unsubscribes();
    }

  private:
    struct Observer
    {
      SubscriptionId id;
      Callback callback;
    };

    std::shared_ptr<ObservableState> _state =
        std::make_shared<ObservableState>();

    T _value{};

    SubscriptionId _next_subscription_id = 0;
    bool _notifying = false;

    std::vector<Observer> _observers;
    std::vector<Observer> _pending_observers;
    std::vector<SubscriptionId> _pending_unsubscribes;

    void process_pending_subscribes()
    {
      _observers.insert(
          _observers.end(),
          std::make_move_iterator(_pending_observers.begin()),
          std::make_move_iterator(_pending_observers.end()));

      _pending_observers.clear();
    }

    void process_pending_unsubscribes()
    {
      for (SubscriptionId id : _pending_unsubscribes)
      {
        remove_observer(id);
      }
      _pending_unsubscribes.clear();
    }

    void remove_observer(SubscriptionId id)
    {
      auto it = std::find_if(
          _observers.begin(),
          _observers.end(),
          [id](const Observer &observer)
          {
            return observer.id == id;
          });

      if (it != _observers.end())
      {
        _observers.erase(it);
      }
    }
  };
}