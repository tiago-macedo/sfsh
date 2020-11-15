# TODO SegFaultShell

## Minimal Viable Product
- [ ] Current directory
	- [ ] Directory traversal
	- [ ] Relative and absolute paths
- [ ] proc struct (for process PIDs and names)
- [ ] Execute programs
	- [ ] Access to environment variables
	- [ ] $PATH
- [ ] Built-in functionality
	- [ ] cd
	- [ ] ...&
	- [ ] Actual background
- [ ] Signal handling

## Known Bugs
- [ ] Segfault on empty input

## Sure Would Be Nice To Have These
- [ ] Transform has_proc() (returns 0 or 1) into proc_index() (returns index of process, -1 if process not there)
- [ ] History of commands
	- [ ] Pressing "up" goes throught history
- [~] Error handling

## Eyecandy
- [ ] Colored prompt
