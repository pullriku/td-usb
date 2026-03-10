# Repository Guidelines

## Project Structure & Module Organization
- Core CLI entrypoint and shared logic live at the repository root: `td-usb.c`, `tddevice.c`, `device_types.c`, and headers such as `td-usb.h`.
- Device-specific implementations are in `devices/` (typically one source file per supported model family).
- Platform layers are split by OS:
  - `linux/` contains libusb/POSIX implementations used by `make` builds.
  - `windows/` plus `td-usb.sln` / `td-usb.vcxproj` support Visual Studio builds.
- Documentation is in `docs/`, with user-facing guides in `README.md` and `README_ja.md`.

## Build, Test, and Development Commands
- `make` — builds Linux CLI binary `./td-usb` using `gcc` and `libusb`.
- `make clean` — removes `td-usb` and object artifacts.
- `./td-usb` — prints version/usage for a quick smoke check.
- `./td-usb <model_name> get` — sample runtime check against a connected device.
- On Windows, open `td-usb.sln` in Visual Studio and build the project (exclude `linux/` sources there).

## Coding Style & Naming Conventions
- Language: C (C99-style usage in current codebase).
- Indentation uses tabs; follow existing brace/newline style in touched files.
- Prefer `snake_case` for functions/variables (`parse_args`, `throw_exception`).
- Keep model identifiers and operation strings consistent with existing CLI vocabulary (`get`, `set`, `listen`, `save`, `destroy`).
- Reuse shared abstractions (`td_context_t`, device type interfaces) rather than introducing per-file ad hoc patterns.

## Testing Guidelines
- There is no dedicated automated test suite yet.
- Validate changes with targeted manual checks:
  - Build: `make`
  - CLI sanity: `./td-usb`
  - Feature path: run the affected command on a supported device.
- For bug fixes, include reproducible command examples and expected output in PR notes.

## Commit & Pull Request Guidelines
- Follow the existing concise, imperative style seen in history (e.g., `Add TDFA50607 Support`, `Fix a bug on compile`).
- Keep commits focused (one feature/fix per commit when practical).
- PRs should include:
  - What changed and why
  - Target device/model(s)
  - Build/validation steps run (`make`, sample command)
  - Linked issue(s), if applicable

## Security & Configuration Tips
- Do not commit local environment files or secrets.
- Linux users may need a `udev` rule for non-root USB access; document any VID/PID-specific setup in PRs that add new devices.
