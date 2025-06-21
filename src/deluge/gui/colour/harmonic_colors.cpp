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
#include "model/settings/runtime_feature_settings.h"

namespace deluge::gui::colour {

// Chromatic color mapping (half steps): C=Red, C#=Orange, D=Orange-Yellow, D#=Yellow, E=Yellow-Green,
// F=Green, F#=Cyan-Green, G=Cyan, G#=Blue-Cyan, A=Blue, A#=Indigo, B=Violet
const RGB NoteColorMapping::chromaticNoteColors[12] = {
	RGB(255, 0, 0),     // C  - Red
	RGB(255, 128, 0),   // C# - Orange
	RGB(255, 192, 0),   // D  - Orange-Yellow
	RGB(255, 255, 0),   // D# - Yellow
	RGB(192, 255, 0),   // E  - Yellow-Green
	RGB(0, 255, 0),     // F  - Green
	RGB(0, 255, 128),   // F# - Cyan-Green
	RGB(0, 255, 255),   // G  - Cyan
	RGB(0, 128, 255),   // G# - Blue-Cyan
	RGB(0, 0, 255),     // A  - Blue
	RGB(75, 0, 130),    // A# - Indigo
	RGB(128, 0, 255)    // B  - Violet
};

// Harmonic mapping (circle of fifths)
// Index order: C, C#, D, D#, E, F, F#, G, G#, A, A#, B
const RGB NoteColorMapping::harmonicNoteColors[12] = {
	RGB(255,   0,   0),   // C  – Red
	RGB(  0, 255, 255),   // C# – Cyan
	RGB(255, 192,   0),   // D  – Orange-Yellow
	RGB(  0,   0, 255),   // D# – Blue
	RGB(192, 255,   0),   // E  – Yellow-Green
	RGB(128,   0, 255),   // F  – Violet
	RGB(  0, 255, 128),   // F# – Cyan-Green
	RGB(255, 128,   0),   // G  – Orange
	RGB(  0, 128, 255),   // G# – Blue-Cyan
	RGB(255, 255,   0),   // A  – Yellow
	RGB( 75,   0, 130),   // A# – Indigo
	RGB(  0, 255,   0)    // B  – Green
};

RGB NoteColorMapping::getNoteColor(uint8_t note) {
	uint8_t noteInOctave = note % 12;

	// Get the current mapping mode from runtime settings
	auto mappingMode = static_cast<NoteColorMappingMode>(
		runtimeFeatureSettings.get(RuntimeFeatureSettingType::NoteColorMapping));

	switch (mappingMode) {
		case NoteColorMappingChromatic:
			return getChromaticNoteColor(noteInOctave);
		case NoteColorMappingHarmonic:
			return getHarmonicNoteColor(noteInOctave);
		default:
			// Return default color (this shouldn't happen when feature is enabled)
			return RGB::fromHue(note * -8 / 3);
	}
}

RGB NoteColorMapping::getChromaticNoteColor(uint8_t noteInOctave) {
	if (noteInOctave >= 12) {
		noteInOctave = noteInOctave % 12;
	}
	return chromaticNoteColors[noteInOctave];
}

RGB NoteColorMapping::getHarmonicNoteColor(uint8_t noteInOctave) {
	if (noteInOctave >= 12) {
		noteInOctave = noteInOctave % 12;
	}
	return harmonicNoteColors[noteInOctave];
}

} // namespace deluge::gui::colour
