#include <linux/string.h> 
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>
struct birthday{
    char *id;
    char *class;
    char *sex;
    int day;
    int month;
    int year;
    char* name;
    struct list_head list;
};
static LIST_HEAD(birthday_list);

//進入 kernel module
int simple_init(void){
    struct birthday *ptr;
    struct birthday *person, *person2, *person3, *person4, *person5;
    struct birthday *firstperson, *tailperson;

    firstperson = kmalloc(sizeof(*firstperson), GFP_KERNEL);
    firstperson->name=kmalloc(sizeof("Matt"), GFP_KERNEL);
    strcpy(firstperson->name, "Matt");
    firstperson->id=kmalloc(sizeof("D1000001"), GFP_KERNEL);
    strcpy(firstperson->id, "D1000001");
    firstperson->class=kmalloc(sizeof("IECS A"), GFP_KERNEL);
    strcpy(firstperson->class, "IECS A");
    firstperson->sex=kmalloc(sizeof("male"), GFP_KERNEL);
    strcpy(firstperson->sex, "male");
    firstperson->day=4;
    firstperson->month=4;
    firstperson->year=2003;

    person = kmalloc(sizeof(*person), GFP_KERNEL);
    person->name=kmalloc(sizeof("Jane"), GFP_KERNEL);
    strcpy(person->name, "Jane");
    person->id=kmalloc(sizeof("D1000002"), GFP_KERNEL);
    strcpy(person->id, "D1000002");
    person->class=kmalloc(sizeof("IECS A"), GFP_KERNEL);
    strcpy(person->class, "IECS A");
    person->sex=kmalloc(sizeof("female"), GFP_KERNEL);
    strcpy(person->sex, "female");
    person->day=22;
    person->month=7;
    person->year=2018; 

    person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
    person2->name=kmalloc(sizeof("Michael"), GFP_KERNEL);
    strcpy(person2->name, "Michael");
    person2->id=kmalloc(sizeof("D1000003"), GFP_KERNEL);
    strcpy(person2->id, "D1000003");
    person2->class=kmalloc(sizeof("IECS B"), GFP_KERNEL);
    strcpy(person2->class, "IECS B");
    person2->sex=kmalloc(sizeof("female"), GFP_KERNEL);
    strcpy(person2->sex, "female");
    person2->day=4;
    person2->month=3;
    person2->year=2018;

    person3 = kmalloc(sizeof(*person3), GFP_KERNEL);
    person3->name=kmalloc(sizeof("Lacey"), GFP_KERNEL);
    strcpy(person3->name, "Lacey");
    person3->id=kmalloc(sizeof("D1000004"), GFP_KERNEL);
    strcpy(person3->id, "D1000004");
    person3->class=kmalloc(sizeof("IECS B"), GFP_KERNEL);
    strcpy(person3->class, "IECS B");
    person3->sex=kmalloc(sizeof("female"), GFP_KERNEL);
    strcpy(person3->sex, "female");
    person3->day=4;
    person3->month=3;
    person3->year=2018;

    person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
    person4->name=kmalloc(sizeof("Tom"), GFP_KERNEL);
    strcpy(person4->name, "Tom");
    person4->id=kmalloc(sizeof("D1000005"), GFP_KERNEL);
    strcpy(person4->id, "D1000005");
    person4->class=kmalloc(sizeof("IECS C"), GFP_KERNEL);
    strcpy(person4->class, "IECS C");
    person4->sex=kmalloc(sizeof("male"), GFP_KERNEL);
    strcpy(person4->sex, "male");
    person4->day=4; 
    person4->month=4;
    person4->year=2018; 

    person5 = kmalloc(sizeof(*person5), GFP_KERNEL);
    person5->name=kmalloc(sizeof("Stuart"), GFP_KERNEL);
    strcpy(person5->name, "Stuart");
    person5->id=kmalloc(sizeof("D1000006"), GFP_KERNEL);
    strcpy(person5->id, "D1000006");
    person5->class=kmalloc(sizeof("IECS C"), GFP_KERNEL);
    strcpy(person5->class, "IECS C");
    person5->sex=kmalloc(sizeof("male"), GFP_KERNEL);
    strcpy(person5->sex, "male");
    person5->day=4;
    person5->month=5; 
    person5->year=2018;
    
    tailperson = kmalloc(sizeof(*tailperson), GFP_KERNEL);
    tailperson->name=kmalloc(sizeof("Ailce"), GFP_KERNEL);
    strcpy(tailperson->name, "Ailce");
    tailperson->id=kmalloc(sizeof("D1000007"), GFP_KERNEL);
    strcpy(tailperson->id, "D1000007");
    tailperson->class=kmalloc(sizeof("IECS D"), GFP_KERNEL);
    strcpy(tailperson->class, "IECS D");
    tailperson->sex=kmalloc(sizeof("male"), GFP_KERNEL);
    strcpy(tailperson->sex, "male");
    tailperson->day=24;
    tailperson->month=3; 
    tailperson->year=2005;

    INIT_LIST_HEAD (&firstperson->list);
    list_add_tail(&firstperson->list, &birthday_list);
    list_add_tail(&person->list, &birthday_list); 
    list_add_tail(&person2->list, &birthday_list);
    list_add_tail(&person3->list, &birthday_list);
    list_add_tail(&person4->list, &birthday_list);
    list_add_tail(&person5->list, &birthday_list);
    list_add_tail(&tailperson->list, &birthday_list);

    printk(KERN_INFO "loading module\n");

    list_for_each_entry (ptr,&birthday_list, list){ 
        printk(KERN_ALERT "ID: %s, Name: %-8s, Class: %s, Sex: %-6s, Birthday: %d/%d/%d\n",ptr ->id ,ptr ->name, ptr ->class, ptr ->sex, ptr->month, ptr->day,ptr->year);
    } 
    return 0;
}

 // kernel module
void simple_exit(void){
    struct birthday *ptr, *next;
    list_for_each_entry_safe (ptr, next, &birthday_list, list){
        list_del(&ptr->list);
        kfree(ptr);
    }
    printk(KERN_INFO "Removing module\n"); //進入或離開 kernel
}

module_init(simple_init);
module_exit(simple_exit);  

MODULE_LICENSE("GPL");