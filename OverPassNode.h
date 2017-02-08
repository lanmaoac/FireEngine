#ifndef _Node_H__
#define _Node_H__
#include <vector>
#include <string>
#include <map>
#include <algorithm>
namespace OverPass
{
	class Node
	{
	public:
		typedef map<String, Node*> ChildNodeMap;
	protected:

		Node* mParent;
		
		ChildNodeMap mChildren:

		typedef set<Node*>::type ChildUpdateSet;
		ChildUpdateSet mChildrenToUpdate;

		String mName;

		Quaterion mOrientation;
		Vector3 mPosition;
		Vector3 mScale;

		bool mNeedChildUpdate;
		bool mNeedParentUpdate;
		bool mInheritOrientation;
		bool mInheritScale;


		virtual void setParent(Node *parent);
		mutable Quaternion mDerivedOrientation;
		mutable Vector3 mDerivedPosition;
		mutable Vector3 mDerivedScale;

		void _updateFromParent(void) const;

		virtual Node* createChildImpl(void) = 0;
		virtual Node* createChildImpl(const String& name) = 0;

	public :
		Node();
		Node(const String& name);
		
		virtual ~Node();

		const String& getName(void) const { return mName; }
		Node* getParent(void) const { return mParent };

		
		void setOrientation(const Quaternion& q);
		//real or float
		void setOrintation();
		const Quaterion & getOrientation() const { return mOrientation };

		void setPosition(const Vector3& pos);
		//real or float 
		void setPosition();
		const Vector3 & getPosition(void) const { return mPosition; }


		void setScale(const Vector3& scale);
		//real or floaat 
		void setScale();
		const Vector3& getScale(void) const { return mScale; }


		void setInheritOrientation(bool inherit);
		bool getInheritOrientation() const { return mInheritOrientation; }

		void setInheritScale(bool inherit);
		bool getInheritOrientation()const { return mInheritScale; }


		virtual Node* createChild(
			const Vector3& translate = Vector3::ZERO
			const Quaternion rotate = Quaternion::IDENTITY);

		virtual Node* createChild(const String& name, const Vector3& translate = Vector3::ZERO, const Quaternion& rotate = Quaternion::IDENTITY);

		void addChild(Node* child);

		Node* getChild(unsigned short index)  const;
		Node* getChild(const String& name) const;


		virtual void _update(bool updateChildren, bool parentHasChanged);




	};
}
#endif // _Node_H__