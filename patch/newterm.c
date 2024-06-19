void newterm(const Arg *a) {
	char *tabbed_win;
  switch (fork()) {
  case -1:
    die("fork failed: %s\n", strerror(errno));
    break;
  case 0:
    switch (fork()) {
    case -1:
      fprintf(stderr, "fork failed: %s\n", strerror(errno));
      _exit(1);
      break;
    case 0:
      chdir_by_pid(pid);
			tabbed_win = getenv("XEMBED");
			if (tabbed_win)
				execl("/proc/self/exe", argv0, "-w", tabbed_win, NULL);
			else
				execl("/proc/self/exe", argv0, NULL);
      _exit(1);
      break;
    default:
      _exit(0);
    }
  default:
    wait(NULL);
  }
}

static int chdir_by_pid(pid_t pid) {
  char buf[32];
  snprintf(buf, sizeof buf, "/proc/%ld/cwd", (long)pid);
  return chdir(buf);
}
