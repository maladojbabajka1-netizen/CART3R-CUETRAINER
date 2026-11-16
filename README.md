# Cue Trainer (Geometry Dash / Geode)

An Android64 Geode mod project targeting Geometry Dash **2.2081**.

## What it does
A small in-level HUD shows the next manually-entered action:
- `CLICK NOW`
- `RELEASE NOW`
- or a countdown in seconds.

**Important:** this does not discover the correct inputs for an arbitrary level. The timestamps in `src/main.cpp` are example values and must be replaced with timings for the level/run you want to practise. Times are measured from the start of the level. The cue display is a practice aid, not an auto-player.

## Build from your phone using GitHub Actions
1. Create a GitHub repository and upload the contents of this folder (not the ZIP itself).
2. Make sure the default branch is named `main`.
3. Open the repository's **Actions** tab and run **Build Android Geode mod** (or push a commit to `main`).
4. When the workflow finishes successfully, open that run and download the `Cue-Trainer-Android64` artifact.
5. Extract the artifact and copy the `.geode` file into:
   `/storage/emulated/0/Android/media/com.geode.launcher/game/geode/mods/`
6. Open Geode and enable Cue Trainer.

## Edit timings
Open `src/main.cpp` and edit the `CUES` list. Each entry is:
`{ seconds_from_level_start, true }` for CLICK or
`{ seconds_from_level_start, false }` for RELEASE.

Keep timestamps in increasing order. Commit the change to GitHub; the workflow rebuilds the mod.

## Compatibility / status
This is a source project with a cloud-build workflow, **not a precompiled or device-tested `.geode` file**. The workflow uses Geode's official build action and targets Android64. If your phone/Geode install is 32-bit, this target will not work; the project would need an Android32 build instead.

Official references:
- Geode mod creation/building: https://github.com/geode-sdk/docs/blob/main/getting-started/create-mod.md
- Geode build action: https://github.com/geode-sdk/build-geode-mod
