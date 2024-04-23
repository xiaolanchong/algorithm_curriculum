#include <vector>
#include <memory>
#include <gtest/gtest.h>

struct Node;
using NodePtr = std::unique_ptr<Node>;

struct Node
{
   unsigned int index;
   NodePtr left;
   NodePtr right;
};


TEST(TreeDiameterTest, SimpleTest)
{
   /* auto root = std::make_unique<Node>(1);
   auto node2 = std::make_unique<Node>(2);
   auto node3 = std::make_unique<Node>(3);
   auto root = std::make_unique<Node>(1);
   root->left = std::make_unique<Node>(2);
   root->right = std::make_unique<Node>(3);*/
}