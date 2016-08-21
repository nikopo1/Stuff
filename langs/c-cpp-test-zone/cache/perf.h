#ifndef __PERF_H__
#define __PERF_H__

#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>

static inline long perf_event_open(struct perf_event_attr *hw_event,
	pid_t pid, int cpu, int group_fd, unsigned long flags)
{
	int ret;

	ret = syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);

	return ret;
}

static inline int perf_instruction_counter(void)
{
	struct perf_event_attr pe;
	int fd;

	memset(&pe, 0, sizeof(struct perf_event_attr));
	pe.type = PERF_TYPE_HARDWARE;
	pe.size = sizeof(struct perf_event_attr);
	pe.config = PERF_COUNT_HW_INSTRUCTIONS;
	pe.disabled = 1;
	pe.exclude_kernel = 1;
	pe.exclude_hv = 1;
	pe.pinned = 1;

	fd = perf_event_open(&pe, 0, -1, -1, 0);

	return fd;
}

static inline int perf_cpu_cycle_counter(void)
{
	struct perf_event_attr pe;
	int fd;

	memset(&pe, 0, sizeof(struct perf_event_attr));
	pe.type = PERF_TYPE_HARDWARE;
	pe.size = sizeof(struct perf_event_attr);
	pe.config = PERF_COUNT_HW_CPU_CYCLES;
	pe.disabled = 1;
	pe.exclude_kernel = 1;
	pe.exclude_hv = 1;
	pe.pinned = 1;

	fd = perf_event_open(&pe, 0, -1, -1, 0);

	return fd;
}

static inline int perf_ref_cpu_cycle_counter(void)
{
	struct perf_event_attr pe;
	int fd;

	memset(&pe, 0, sizeof(struct perf_event_attr));
	pe.type = PERF_TYPE_HARDWARE;
	pe.size = sizeof(struct perf_event_attr);
	pe.config = PERF_COUNT_HW_REF_CPU_CYCLES;
	pe.disabled = 1;
	pe.exclude_kernel = 1;
	pe.exclude_hv = 1;
	pe.pinned = 1;

	fd = perf_event_open(&pe, 0, -1, -1, 0);

	return fd;
}

static inline int perf_start(int counter_fd)
{
	int ret;

	ret = ioctl(counter_fd, PERF_EVENT_IOC_RESET, 0);
	if(ret < 0) {
		return ret;
	}

	ret = ioctl(counter_fd, PERF_EVENT_IOC_ENABLE, 0);
	
	return ret;
}

static inline int perf_stop(int counter_fd)
{
	int ret;

	ret = ioctl(counter_fd, PERF_EVENT_IOC_DISABLE, 0);

	return ret;
}

static inline long long perf_read_counter(int counter_fd)
{
	int ret;
	long long count;

	ret = read(counter_fd, &count, sizeof(long long));

	if(ret < 0) {
		return (long long) ret;
	}

	return count;
}

#endif /* __PERF_H__ */

