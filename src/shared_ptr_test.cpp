#include"shared_ptr.hpp"
#include <memory>

using namespace vv_memory;
using std::cout;
using std::endl;

struct ListNode{
    int data_;
    std::weak_ptr<ListNode> pre_;
    std::weak_ptr<ListNode> next_;
    ~ListNode(){
        std::cout<<"~ListNode() destruct"<<'\n';
    }
};

int main()
{
    SharedPtr<int> sp1(new int(10));
    SharedPtr<int> sp2(sp1);
    *sp2 = 20;
                                                                //sp1 与 sp2 在管理这部分资源，引用计数为 2
    cout << sp1.get_count()<< "  *ptr:" << *sp1 << endl;		//2	 20
    cout << sp2.get_count() << "  *ptr:" << *sp2 << endl;		//2	 20
                                                                  
    SharedPtr<int> sp3(new int(30));                              
    sp2 = sp3;		                                            //sp3 赋值给它，释放管理的旧资源，引用计数-1，   
    cout << sp1.get_count() << "  *ptr:" << *sp1 << endl;        //1	 20
    cout << sp2.get_count() << "  *ptr:" << *sp2 << endl;        //2	 30
    cout << sp3.get_count() << "  *ptr:" << *sp3 << endl;        //2	 30
                                                                  
    sp1 = sp3;                                                    
    cout << sp1.get_count() << "  *ptr:" << *sp1 << endl;        //3	 30
    cout << sp2.get_count() << "  *ptr:" << *sp2 << endl;        //3	 30
    cout << sp3.get_count() << "  *ptr:" << *sp3 << endl;        //3	 30

    std::cout << "Hello World!\n";
    return 0;
}