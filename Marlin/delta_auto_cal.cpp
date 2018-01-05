/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "MarlinConfig.h"

#if ENABLED(DELTA_AUTO_CALIBRATION)

#include "delta_auto_cal.h"
#include "Marlin.h"

void refresh_auto_cal_ref(float z_shift){
  static float cal_zoffset,
               cal_height,
               cal_endstop_adj[ABC],
               cal_radius,
               cal_tower_angle_trim[ABC],
               cal_diagonal_rod;

  if (!isnan(z_shift)){
    z_shift += zprobe_zoffset - cal_zoffset;
    zprobe_zoffset = cal_zoffset + z_shift;
    delta_height = cal_height - z_shift;
    COPY(delta_endstop_adj, cal_endstop_adj);
    delta_radius = cal_radius;
    COPY(delta_tower_angle_trim, cal_tower_angle_trim);
    delta_diagonal_rod = cal_diagonal_rod;
  }
  cal_zoffset = zprobe_zoffset;
  cal_height = delta_height;
  COPY(cal_endstop_adj, delta_endstop_adj);
  cal_radius = delta_radius;
  COPY(cal_tower_angle_trim, delta_tower_angle_trim);
  cal_diagonal_rod = delta_diagonal_rod;
}

#endif // DELTA_AUTO_CALIBRATION
