#include <sys/types.h>
#include <unistd.h>
#include <utils/Log.h>
#include <utils/List.h>

using namespace android;

typedef struct{
	int num;
	char data[128];
}NodeTest;

void show(List<NodeTest*> list)
{
	List<NodeTest*>::iterator iter ;	 
	for(iter = list.begin(); iter != list.end(); iter++)
	{
		printf("num:%d data:%s\n",(*iter)->num,(*iter)->data);
	}
	
}


int main(int argc, char** argv)
{
	List<NodeTest*> list;
	//node = (NodeTest *)malloc(sizeof(NodeTest));
	NodeTest *node = new NodeTest;
	node->num = 0;
	sprintf(node->data,"123");
	list.push_back(node);	
	show(list);

	node = new NodeTest;
	node->num = 1;
	sprintf(node->data,"456");
	list.push_back(node);
	show(list);
	

	list.erase(list.begin());
	show(list);

    return 0;
}
