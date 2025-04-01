#pragma once

#ifndef ABSTRACTTREENODE_H
# define ABSTRACTTREENODE_H

class AbstractTreeNode
{
public:
  explicit AbstractTreeNode();
  virtual ~AbstractTreeNode() = 0;
public:
  virtual std::string getSimpleName() const = 0;
  virtual std::string getCompleteName() const = 0;
};

#endif // !ABSTRACTTREENODE_H
