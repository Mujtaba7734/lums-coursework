#include "../include/post_pool.h"
using namespace std;

PostPool::PostPool(size_t block_size): block_size(block_size) 
{
    current_block_index = 0;
    alloc_count = 0;
    reuse_count = 0;
    allocateBlock();
}

PostPool::~PostPool() {
    purge();
}

Post* PostPool::allocPost() { 

    if (!free_list.empty()) 
    {
        Post *p = free_list.back(); //! assigns p a memory position from the free_list vector
        free_list.pop_back(); //! removes the free position from the vector
        reuse_count++;
        return p;
    }

    if (current_block_index >= block_size) allocateBlock();  //! checks whether block is full, if yes, then allocates another block to it
    
    Post *p = &blocks.back()[current_block_index]; //! assigns the current block index a value
    current_block_index++;
    return p;
   
}

void PostPool::freePost(Post* p) {
   if (!p) return;
   p->postID = 0;
   p->content = "";
   p->views = 0;
   p->category = "";

   free_list.push_back(p);
   reuse_count++;
}

size_t PostPool::totalAllocations() const {
    return alloc_count;
}

size_t PostPool::reuseCount() const {
    return reuse_count;
}

void PostPool::purge() {
    for (size_t i =0; i < blocks.size(); i++){
        Post *block = blocks[i];
        delete [] block;
    }
    blocks.clear();
    free_list.clear();
    current_block_index =0;
    alloc_count = 0;
    reuse_count = 0;
}

void PostPool::allocateBlock() {
   Post *newblock = new Post[block_size];
   blocks.push_back(newblock);
   current_block_index =0;
   alloc_count+= block_size;
}