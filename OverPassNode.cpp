#include "OverPassNode.h"
namespace OverPass
{
	Node::Node()
		:mParent(0),
		mPosition(Vector3::ZERO),
		mScale(Vector3::UNIT_SCALE),
		mInheritOrientation(true),
		mInheritScale(true)
	{
		mName = "hehe";
		needUpdate();
	}
	Node::Node(const  String& name)
		:mParent(0),
		mPosition(Vector3::ZERO),
		mScale(Vector3::UNIT_SCALE),
		mInheritOrientation(true),
		mInheritScale(true)
	{
		mName = name;
		needUpdate();
	}

	Node::~Node()
	{
		removeAllChildren();
		if (mParent)
			mParent->removeChild(this);

	}
	void Node::setParent(Node  *parent)
	{
		bool different = (parent != mParent);

		needUpdate();
	}
	void Node::_update(bool updateChildren, bool parentHasChanged)
	{
		if (parentHasChanged)
		{
			_updateFromParent();
		}
		if (updateChildren)
		{
			if (mNeedChildUpdate || parentHasChanged)
			{
				ChildNodeMap::iterator it, itend;
				itend = mChildren.end();
				for (it = mChildren.begin(); it != itend; ++it)
				{
					Node *child = it->second;
					child->_update(true,true);
				}
			}
			mNeedChildUpdate = false;
		}
	}
	void Node::_updateFromParent(void) const
	{
		updateFromParent();
	/*
	if (mListener)
	{
	mListener->nodeUpdate(this);
	}
	*/
	}
	void Node::_updateFromParent(void) const
	{
		if (mParent)
		{
			const Quaternion& parentOrientation = mParent->_getDeriveOrientation();
			if (mInheritOrientation)
			{
				mDerivedOrientation = parentOrientation * mOrientation;
			}
			else
			{
				mDerivedOrientation = mOrientation;
			}

			const Vector3& parentScale = mParent->_getDerivedScale();
			if (mInheritScale)
			{
				mDerivedScale = parentScale * mScale;
			}
			else
			{
				mDerivedScale = mScale;
			}
			mDerivedPosition = parentOrientation*(parentScale*mPosition);
			mDerivedPosition += mParent->_getDerivedPosition(0;)
		}
		else
		{
			mDerivedOrientation = mOrientation;
			mDerivedPosition = mPosition;
			mDerivedScale = mScale;
		}
		mNeedParentUpdate = false;
	}
	void Node::addChild(Node* child)
	{
		if (child->mParent)
		{
			//HEHE
		}

		child->setParent(this);
	}
}
