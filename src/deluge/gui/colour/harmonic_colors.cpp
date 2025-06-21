/*
 * Copyright © 2024 Synthstrom Audible Limited
 *
 * This file is part of The Synthstrom Audible Deluge Firmware.
 *
 * The Synthstrom Audible Deluge Firmware is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#include "harmonic_colors.h"

namespace deluge::gui::colour {

RGB HarmonicColors::getNoteColor(uint8_t note) {
    // Map note to octave position (0-11)
    uint8_t noteInOctave = note % 12;
    return getNoteInOctaveColor(noteInOctave);
}

RGB HarmonicColors::getNoteInOctaveColor(uint8_t noteInOctave) {
    // Ensure noteInOctave is within valid range
    if (noteInOctave >= 12) {
        noteInOctave = noteInOctave % 12;
    }
    
    return harmonicNoteColors[noteInOctave];
}

} // namespace deluge::gui::colour 