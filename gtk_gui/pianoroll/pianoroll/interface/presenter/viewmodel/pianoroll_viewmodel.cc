/*
 * Copyright (C) 2023 Paul Davis <paul@linuxaudiosystems.com>
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

#include "pianoroll_viewmodel.h"

namespace MYAPP
{
  PianorollViewModel::PianorollViewModel()
      : _editing_scope({MYAPP::EditingScope::ActiveView})
  {
  }

  void PianorollViewModel::set_editing_scope(EditingScope editing_scope)
  {
    _editing_scope.set(editing_scope);
  }

  GtkObservable<EditingScope> &PianorollViewModel::get_editing_scope_observable()
  {
    return _editing_scope;
  }

  const EditingScope &PianorollViewModel::get_editing_scope() const
  {
    return _editing_scope.get();
  }
}