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

#include "session_controller.h"

namespace MYAPP
{
  const std::string SessionController::class_name = "SessionController";

  SessionController::SessionController(
      SessionRepository *session_repository)
      : _session_repository(session_repository)
  {
  }

  int SessionController::save(
      ARDOUR::Session *session,
      std::string name,
      bool switch_to_snapshot)
  {
    return _session_repository->save(session, name, switch_to_snapshot);
  }
}