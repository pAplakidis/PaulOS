#pragma once
#include <stdint.h>

struct page_dir_entry{
  
}__attribute__((packed));

struct page_table_entry{
  
}__attribute__((packed));

struct page_dir_entry page_directory[1024] __attribute__((aligned(4096)));
