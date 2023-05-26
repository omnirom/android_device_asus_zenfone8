/*
* Copyright (C) 2023 The OmniROM Project
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
*/

package org.omnirom.diracaudio

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.media.audiofx.AudioEffect
import android.util.Log

import java.util.UUID

class BootCompletedReceiver : BroadcastReceiver() {
    private val audioEffect = AudioEffect(
        AudioEffect.EFFECT_TYPE_NULL, DIRAC_EFFECT_UUID, 0, 0
    )

    override fun onReceive(context: Context, intent: Intent) {
        Log.d(TAG, "Starting")
        audioEffect.enabled = true
    }

    companion object {
        private const val TAG = "AsusDiracAudio"

        private val DIRAC_EFFECT_UUID = UUID.fromString("3799D6D1-22C5-43C3-B3EC-D664CF8D2F0D")
    }
}
