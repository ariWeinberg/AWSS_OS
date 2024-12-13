#define FAT12 1
#define FAT16 2
#define FAT32 3
#define ExFAT 4



typedef struct fat_extBS_32
{
	//extended fat32 stuff
	unsigned int		table_size_32;
	unsigned short		extended_flags;
	unsigned short		fat_version;
	unsigned int		root_cluster;
	unsigned short		fat_info;
	unsigned short		backup_BS_sector;
	unsigned char 		reserved_0[12];
	unsigned char		drive_number;
	unsigned char 		reserved_1;
	unsigned char		boot_signature;
	unsigned int 		volume_id;
	unsigned char		volume_label[11];
	unsigned char		fat_type_label[8];

}__attribute__((packed)) fat_extBS_32_t;

typedef struct fat_extBS_16
{
	//extended fat12 and fat16 stuff
	unsigned char		bios_drive_num;
	unsigned char		reserved1;
	unsigned char		boot_signature;
	unsigned int		volume_id;
	unsigned char		volume_label[11];
	unsigned char		fat_type_label[8];
	
}__attribute__((packed)) fat_extBS_16_t;

typedef struct fat_BS
{
	unsigned char 		bootjmp[3];
	unsigned char 		oem_name[8];
	unsigned short 	        bytes_per_sector;
	unsigned char		sectors_per_cluster;
	unsigned short		reserved_sector_count;
	unsigned char		table_count;
	unsigned short		root_entry_count;
	unsigned short		total_sectors_16;
	unsigned char		media_type;
	unsigned short		table_size_16;
	unsigned short		sectors_per_track;
	unsigned short		head_side_count;
	unsigned int 		hidden_sector_count;
	unsigned int 		total_sectors_32;
	
	//this will be cast to it's specific type once the driver actually knows what type of FAT this is.
	unsigned char		extended_section[54];
	
}__attribute__((packed)) fat_BS_t;

typedef struct extended_data
{
    unsigned int total_sectors;
    unsigned int fat_size;
    unsigned long root_dir_sectors;
    unsigned short first_data_sector;
    unsigned short first_fat_sector;
    unsigned long long data_sectors;
    unsigned int total_clusters;

    unsigned short fat_type;
}__attribute__((packed)) extended_data_t;

typedef struct fs_data
{
    
}__attribute__((packed)) fs_data_t;


extended_data_t GetExtendedData(fat_BS_t* fat_boot)
{
    extended_data_t result;
    fat_extBS_32_t fat_boot_ext_32;

    result.total_sectors = (fat_boot->total_sectors_16 == 0)? fat_boot->total_sectors_32 : fat_boot->total_sectors_16;
    result.fat_size = (fat_boot->table_size_16 == 0)? fat_boot_ext_32.table_size_32 : fat_boot->table_size_16;
    result.root_dir_sectors = ((fat_boot->root_entry_count * 32) + (fat_boot->bytes_per_sector - 1)) / fat_boot->bytes_per_sector;
    result.first_data_sector = fat_boot->reserved_sector_count + (fat_boot->table_count * result.fat_size) + result.root_dir_sectors;
    result.first_fat_sector = fat_boot->reserved_sector_count;
    result.data_sectors = result.total_sectors - (fat_boot->reserved_sector_count + (fat_boot->table_count * result.fat_size) + result.root_dir_sectors);
    result.total_clusters = result.data_sectors / fat_boot->sectors_per_cluster;
    if (0)//sectorsize == 0) 
    {
        result.fat_type = ExFAT;
    }
    else if(result.total_clusters < 4085) 
    {
        result.fat_type = FAT12;
    } 
    else if(result.total_clusters < 65525) 
    {
        result.fat_type = FAT16;
    } 
    else
    {
        result.fat_type = FAT32;
    }    
}



extended_data_t* ext_data;
fat_extBS_32_t* extBS_32;




typedef struct directory_entrey
{
    
    unsigned short int file_name [11]; 
    unsigned short int attributes; 
    unsigned short int reserved; 
    unsigned int creation_time;
    unsigned int time_of_creation;
    unsigned int date_of_creation;
    unsigned int last_accessed_date;
    unsigned int first_cluster_high;
    unsigned int last_modification_time;
    unsigned int last_modification_date;
    unsigned int first_cluster_low;
    unsigned long int file_size;



}__attribute__((packed)) directory_entrey_t;

typedef struct lfn_entrey
{
    
    unsigned short int sequqnce_order;
    unsigned short int entrey_value_first_5[10];
    unsigned short int attribiute;
    unsigned short int long_entrey_type;
    unsigned short int short_name_checksum;
    unsigned short int entrey_value_next_6[12];
    unsigned int reserved_zero;
    unsigned short int entrey_value_last_2[4];
}__attribute__((packed)) lfn_entrey_t;
