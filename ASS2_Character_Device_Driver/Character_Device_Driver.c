#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/fs.h>
#include <linux/uaccess.h> 
#include <linux/string.h>
#include <linux/utsname.h> 


MODULE_LICENSE("GPL");

#define BUFFER_SIZE 1024 


static int kernel_version[3];

static int open_count = 0;
static char kernel_buffer[BUFFER_SIZE];
int kernel_version_len = 3; 
module_param_array(kernel_version, int, &kernel_version_len, 0644);
int major_num = 0;


// Function prototypes for file operations
ssize_t dev_read(struct file *pfile, char __user *user_buffer, size_t len, loff_t *offset);
ssize_t dev_write(struct file *pfile, const char __user *user_buffer, size_t len, loff_t *offset);
int dev_open(struct inode *pinode, struct file *pfile);
int dev_close(struct inode *pinode, struct file *pfile);

/*To hold the file operation on this device*/
	ssize_t dev_read(struct file *pfile, char __user *user_buffer, size_t len, loff_t *offset){
		printk(KERN_INFO "Read function called!\n");
		size_t bytes_to_read = strlen(kernel_buffer);
		

    		if (*offset >= bytes_to_read) {
		        return 0;
    		}

		if (len > bytes_to_read - *offset) {
			len = bytes_to_read - *offset;
		}

		if (copy_to_user(user_buffer, kernel_buffer + *offset, len)) {
		        return -EFAULT;
		}

		*offset += len;
		printk(KERN_INFO "Sent to user: %s\n", kernel_buffer);
		return len;
	}
	
        ssize_t dev_write(struct file *pfile, const char __user *user_buffer, size_t len,loff_t *offset){
        	printk(KERN_INFO "Write function called!\n");
        	 if (len > BUFFER_SIZE - 1) {
        		return -EFAULT;
    		}
    		if (copy_from_user(kernel_buffer, user_buffer, len)) {
        		return -EFAULT;
    		}
    		kernel_buffer[len] = '\0';
    		printk(KERN_INFO "Received from user: %s\n", kernel_buffer);
    		return len;
        	
        }
        
	int dev_open(struct inode *pinode, struct file *pfile){
		open_count++;
    		printk(KERN_INFO "Device opened %d'th times\n", open_count);
    		return 0;
	}
	
	int dev_close(struct inode *pinode, struct file *pfile){
		printk(KERN_INFO "Device closed\n");
    		return 0;
	}
	 
struct file_operations char_driver_file_operations = {
	.owner   = THIS_MODULE,
	.open    = dev_open,
	.read    = dev_read,
	.write   = dev_write,
	.release = dev_close,
};


static int __init Character_Device_Driver_init(void){
    int running_version[3];
    struct new_utsname *uts;

    uts = utsname();
    
    sscanf(uts->release, "%d.%d.%d", &running_version[0], &running_version[1], &running_version[2]);
    printk(KERN_ALERT "kernal : %d,%d,%d",kernel_version[0], kernel_version[1], kernel_version[2]);
    if (kernel_version[0] != running_version[0] || 
        kernel_version[1] != running_version[1] || 
        kernel_version[2] != running_version[2]) {
        printk(KERN_ALERT "Kernel Version Mismatch: Expected %d.%d.%d, but got %d.%d.%d\n",
               running_version[0], running_version[1], running_version[2],
               kernel_version[0], kernel_version[1], kernel_version[2] );
        return -EINVAL;
    }

    major_num = register_chrdev(0, "Character_Driver", &char_driver_file_operations);
    if (major_num < 0) {
        printk(KERN_ALERT "Failed to register character driver\n");
        return major_num;
    }

    printk(KERN_INFO "Character driver registered with major number: %d & minor number: %d\n", major_num,0);
    return 0;
}

static void Character_Device_Driver_exit(void){
	printk(KERN_ALERT "Inside the %s Function\n",__FUNCTION__);
	/*Unregister the char device drv*/
	unregister_chrdev(511,"Character_Driver");
}


module_init(Character_Device_Driver_init);
module_exit(Character_Device_Driver_exit);



