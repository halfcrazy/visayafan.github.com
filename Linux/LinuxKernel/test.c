struct task_struct {
	volatile long state;	/* -1 unrunnable, 0 runnable, >0 stopped */
	struct thread_info *thread_info;
	atomic_t usage;
	unsigned long flags;	/* per process flags, defined below */
	unsigned long ptrace;

	int lock_depth;		/* Lock depth */

	int prio, static_prio;
	struct list_head run_list;
	prio_array_t *array;

	unsigned long sleep_avg;
	unsigned long long timestamp, last_ran;
	int activated;

	unsigned long policy;
	cpumask_t cpus_allowed;
	unsigned int time_slice, first_time_slice;

#ifdef CONFIG_SCHEDSTATS
	struct info sched_info;
#endif

	struct list_head tasks;
	/*
	 * ptrace_list/ptrace_children forms the list of my children
	 * that were stolen by a ptracer.
	 */
	struct list_head ptrace_children;
	struct list_head ptrace_list;

	struct mm_struct *mm, *active_mm;

/* task state */
	struct linux_binfmt *binfmt;
	long exit_state;
	int exit_code, exit_signal;
	int pdeath_signal;  /*  The signal sent when the parent dies  */
	/* ??? */
	unsigned long personality;
	unsigned did_exec:1;
	pid_t pid;
	pid_t tgid;
	/* 
	 * pointers to (original) parent process, youngest child, younger sibling,
	 * older sibling, respectively.  (p->father can be replaced with 
	 * p->parent->pid)
	 */
	struct task_struct *real_parent; /* real parent process (when being debugged) */
	struct task_struct *parent;	/* parent process */
	/*
	 * children/sibling forms the list of my children plus the
	 * tasks I'm ptracing.
	 */
	struct list_head children;	/* list of my children */
	struct list_head sibling;	/* linkage in my parent's children list */
	struct task_struct *group_leader;	/* threadgroup leader */

	/* PID/PID hash table linkage. */
	struct pid pids[PIDTYPE_MAX];

	struct completion *vfork_done;		/* for vfork() */
	int __user *set_child_tid;		/* CLONE_CHILD_SETTID */
	int __user *clear_child_tid;		/* CLONE_CHILD_CLEARTID */

	unsigned long rt_priority;
	unsigned long it_real_value, it_real_incr;
	cputime_t it_virt_value, it_virt_incr;
	cputime_t it_prof_value, it_prof_incr;
	struct timer_list real_timer;
	cputime_t utime, stime;
	unsigned long nvcsw, nivcsw; /* context switch counts */
	struct timespec start_time;
/* mm fault and swap info: this can arguably be seen as either mm-specific or thread-specific */
	unsigned long min_flt, maj_flt;
/* process credentials */
	uid_t uid,euid,suid,fsuid;
	gid_t gid,egid,sgid,fsgid;
	struct group_info *group_info;
	kernel_cap_t   cap_effective, cap_inheritable, cap_permitted;
	unsigned keep_capabilities:1;
	struct user_struct *user;
#ifdef CONFIG_KEYS
	struct key *session_keyring;	/* keyring inherited over fork */
	struct key *process_keyring;	/* keyring private to this process (CLONE_THREAD) */
	struct key *thread_keyring;	/* keyring private to this thread */
#endif
	int oomkilladj; /* OOM kill score adjustment (bit shift). */
	char comm[TASK_COMM_LEN];
/* file system info */
	int link_count, total_link_count;
/* ipc stuff */
	struct sysv_sem sysvsem;
/* CPU-specific state of this task */
	struct thread_struct thread;
/* filesystem information */
	struct fs_struct *fs;
/* open file information */
	struct files_struct *files;
/* namespace */
	struct namespace *namespace;
/* signal handlers */
	struct signal_struct *signal;
	struct sighand_struct *sighand;

	sigset_t blocked, real_blocked;
	struct sigpending pending;

	unsigned long sas_ss_sp;
	size_t sas_ss_size;
	int (*notifier)(void *priv);
	void *notifier_data;
	sigset_t *notifier_mask;
	
	void *security;
	struct audit_context *audit_context;

/* Thread group tracking */
   	u32 parent_exec_id;
   	u32 self_exec_id;
/* Protection of (de-)allocation: mm, files, fs, tty, keyrings */
	spinlock_t alloc_lock;
/* Protection of proc_dentry: nesting proc_lock, dcache_lock, write_lock_irq(&tasklist_lock); */
	spinlock_t proc_lock;
/* context-switch lock */
	spinlock_t switch_lock;

/* journalling filesystem info */
	void *journal_info;

/* VM state */
	struct reclaim_state *reclaim_state;

	struct dentry *proc_dentry;
	struct backing_dev_info *backing_dev_info;

	struct io_context *io_context;

	unsigned long ptrace_message;
	siginfo_t *last_siginfo; /* For ptrace use.  */
/*
 * current io wait handle: wait queue entry to use for io waits
 * If this thread is processing aio, this points at the waitqueue
 * inside the currently handled kiocb. It may be NULL (i.e. default
 * to a stack based synchronous wait) if its doing sync IO.
 */
	wait_queue_t *io_wait;
/* i/o counters(bytes read/written, #syscalls */
	u64 rchar, wchar, syscr, syscw;
#if defined(CONFIG_BSD_PROCESS_ACCT)
	u64 acct_rss_mem1;	/* accumulated rss usage */
	u64 acct_vm_mem1;	/* accumulated virtual memory usage */
	clock_t acct_stimexpd;	/* clock_t-converted stime since last update */
#endif
#ifdef CONFIG_NUMA
  	struct mempolicy *mempolicy;
	short il_next;
#endif
};


DEFINE_WAIT(wait);
prepare_to_wait_exclusive(&wq, &wait, TASK_INTERRUPTIBLE); /* wq is the head of the wait queue */
....
if (!condition)
    schedule();
finish_wait(&wq, &wait);

int clone(int (*fn)(void *), void *child_stack,
                 int flags, void *arg, 
                 /* pid_t *ptid, struct user_desc *tls, pid_t *ctid */ );
/*
 * kernel 2.6.11 之后的内核版本中引入了许多其它的标志，例如:
 * CLONE_NEWNET在一新的网络namespce中创建子进程
 * CLONE_NEWPID在一新的PID namespace中创建一个新的进程
 * CLONE_NEWIPC在一新的IPC namespace中创建一个新的进程
 * CLONE_IO共享IO
 */
#define CSIGNAL		0x000000ff             /* 退出时标志signal mask to be sent at exit */
#define CLONE_VM	0x00000100             /* 共享地址空间set if VM shared between processes */
#define CLONE_FS	0x00000200             /* 共享文件系统set if fs info shared between processes */
#define CLONE_FILES	0x00000400             /* 共享打开文件set if open files shared between processes */
#define CLONE_SIGHAND	0x00000800         /* 共享信息处理器和阻塞信号？,如果此位被置，则CLONE_VM必须也被置 set if signal handlers and blocked signals shared */
#define CLONE_PTRACE	0x00002000         /* 父进程被跟踪时子进程也被跟踪set if we want to let tracing continue on the child too */
#define CLONE_VFORK	0x00004000             /* 父进程被挂起直到子进程释放虚拟内存 set if the parent wants the child to wake it up on mm_release */
#define CLONE_PARENT	0x00008000         /* 共享父进程，即改变父子关系为兄弟关系set if we want to have the same parent as the cloner */
#define CLONE_THREAD	0x00010000         /* 子进程加入父进程的线程组，设置子进程的tgid和group_leader, Same thread group? */
#define CLONE_NEWNS	0x00020000             /* 在新的namespce启动子进程？New namespace group? */
#define CLONE_SYSVSEM	0x00040000         /* share system V SEM_UNDO semantics */
#define CLONE_SETTLS	0x00080000         /* 子进程创建新的thread local segment？？？create a new TLS for the child */
#define CLONE_PARENT_SETTID	0x00100000     /* 设置参数中的pid为子进程的进程号 set the TID in the parent */
#define CLONE_CHILD_CLEARTID	0x00200000 /* 清除子进程的tid， clear the TID in the child */
#define CLONE_DETACHED		0x00400000     /* 保留Unused, ignored */
#define CLONE_UNTRACED		0x00800000 /* 子进程不要被跟踪set if the tracing process can't force CLONE_PTRACE on this clone */
#define CLONE_CHILD_SETTID	0x01000000 /* 设置子进程的tid变量为子进程的ID， set the TID in the child */
#define CLONE_STOPPED		0x02000000 /* 子进程初始状态为TASK_STOPPED, Start in stopped state */


struct user_struct {
	atomic_t __count;           /* 引用计数reference count */
	atomic_t processes;         /* 此用户拥有的进程个数How many processes does this user have? */
	atomic_t files;             /* 此用户拥有的打开文件个数How many open files does this user have? */
	atomic_t sigpending;        /* How many pending signals does this user have? */
	/* protected by mq_lock	*/
	unsigned long mq_bytes;     /* How many bytes can be allocated to mqueue? */
	unsigned long locked_shm;   /* How many pages of mlocked shm ? */
#ifdef CONFIG_KEYS
	struct key *uid_keyring;     /* UID specific keyring */
	struct key *session_keyring; /* UID's default session keyring */
#endif
	/* Hash table maintenance information */
	struct list_head uidhash_list; /* hash表 */
	uid_t uid;
};
