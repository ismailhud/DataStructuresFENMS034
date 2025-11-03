#include <iostream>
#include "XorLinkedList.h"

int main() {
    std::cout << "=== XOR Linked List Demo ===\n";

    XorLinkedList<int> list;

    list.add_to_back(10);
    list.add_to_back(20);
    list.add_to_back(30);

    std::cout << "List count: " << list.count() << "\n";
    std::cout << "Elements (via index): ";
    for (size_t i = 0; i < list.count(); ++i) {
        std::cout << list[i] << " ";
    }
    std::cout << "\n";

    list.add_to_front(5);
    list.add_to_front(2);
    std::cout << "After adding to front:\n";
    for (auto& val : list) std::cout << val << " ";
    std::cout << "\n";

    list.remove_from_front();
    list.remove_from_back();
    std::cout << "After removals:\n";
    for (auto& val : list) std::cout << val << " ";
    std::cout << "\n";

    std::cout << "Reverse the list (swap head/tail)\n";
    list.reverse();
    for (auto& v : list) std::cout << v << " ";
    std::cout << "\n";

    std::cout << "Copying list...\n";
    XorLinkedList<int> copy = list;
    copy.add_to_back(99);

    std::cout << "Original: ";
    for (auto& val : list) std::cout << val << " ";
    std::cout << "\n";

    std::cout << "Copy: ";
    for (auto& val : copy) std::cout << val << " ";
    std::cout << "\n";

    std::cout << "Moving list...\n";
    XorLinkedList<int> moved = std::move(list);
    std::cout << "Moved list: ";
    for (auto& val : moved) std::cout << val << " ";
    std::cout << "\n";

    std::cout << "=== End of Demo ===\n";
    return 0;
}
