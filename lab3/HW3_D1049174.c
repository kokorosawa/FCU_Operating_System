#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched/signal.h>
#include <linux/init.h>
#include <linux/hashtable.h>
#include <linux/slab.h>

static DEFINE_HASHTABLE(task_table, 10);
static DECLARE_HASHTABLE(task_table, 10);

// 宣告一個結構體，用來存放資料
struct task_info
{
    volatile long state;
    int prio;
    int static_prio;
    int normal_prio;
    unsigned int policy;
    int pid;
    char comm[TASK_COMM_LEN];
    struct hlist_node node;
};

static int hello_init(void)
{
    // 宣告兩個task_struct指標
    struct task_struct *pp;

    // 輸出"Hello, world 1\n"
    printk("Hello, world!!!\n");

    hash_init(task_table);

    // 顯示上方欄位
    printk(KERN_ALERT "Name           PID   State  Priority  Policy\n");

    // 遍歷所有process
    for_each_process(pp)
    {
        if (pp->mm == NULL)
        {
            struct task_info *info = kmalloc(sizeof(struct task_info), GFP_KERNEL);
            // 將資料存入結構體
            strcpy(info->comm, pp->comm);
            info->pid = pp->pid;
            info->state = pp->state;
            info->prio = pp->prio;
            info->policy = pp->policy;

            // 將資料加入 hash table
            if (info->pid)
            {
                hash_add(task_table, &info->node, info->pid);
            }
        }
    }

    return 0;
}

static void hello_exit(void)
{
    struct task_info *info;
    unsigned int bkt;

    printk(KERN_INFO "Goodbye World!!!\n");

    // 遍歷 hash table
    hash_for_each(task_table, bkt, info, node)
    {
        // 印出資料
        if (info->prio <= 70)
            printk(KERN_EMERG "KERN_EMERG: %-15s %-5d %-5ld %-5d %-5d\n", info->comm, info->pid, info->state, info->prio, info->policy);
        else
            printk(KERN_INFO "KERN_INFO: %-15s %-5d %-5ld %-5d %-5d\n", info->comm, info->pid, info->state, info->prio, info->policy);
        // 從 hash table 中刪除資料
        hash_del(&info->node);
    }
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");