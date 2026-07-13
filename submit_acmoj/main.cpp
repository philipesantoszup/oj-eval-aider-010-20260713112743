#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>

// Include the necessary headers for the Bint class
#include "data/class-bint.hpp"
#include "data/class-integer.hpp"
#include "data/class-matrix.hpp"
#include "data/list.hpp"

// Include the ACMOJ client
#include "submit_acmoj/acmoj_client.h"

int main() {
    try {
        // Example usage of the Bint class
        Util::Bint b1("12345678901234567890");
        Util::Bint b2("98765432109876543210");
        
        std::cout << "B1: " << b1 << std::endl;
        std::cout << "B2: " << b2 << std::endl;
        
        Util::Bint sum = b1 + b2;
        std::cout << "Sum: " << sum << std::endl;
        
        Util::Bint difference = b1 - b2;
        std::cout << "Difference: " << difference << std::endl;
        
        Util::Bint product = b1 * b2;
        std::cout << "Product: " << product << std::endl;
        
        // Example usage of the Integer class
        Integer i1(42);
        Integer i2(42);
        if (i1 == i2) {
            std::cout << "Integers are equal" << std::endl;
        }
        
        // Example usage of the Matrix class
        Diamond::Matrix<int> m1(2, 2, 1);
        Diamond::Matrix<int> m2(2, 2, 2);
        
        std::cout << "Matrix 1:" << m1 << std::endl;
        std::cout << "Matrix 2:" << m2 << std::endl;
        
        Diamond::Matrix<int> sumMatrix = m1 + m2;
        std::cout << "Matrix sum:" << sumMatrix << std::endl;
        
        Diamond::Matrix<int> productMatrix = m1 * m2;
        std::cout << "Matrix product:" << productMatrix << std::endl;
        
        // Example usage of the list class
        sjtu::list<int> lst;
        lst.push_back(1);
        lst.push_back(2);
        lst.push_back(3);
        
        std::cout << "List contents: ";
        for (int val : lst) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        
        // Example of list operations
        lst.push_front(0);
        lst.pop_back();
        lst.sort();
        lst.reverse();
        
        std::cout << "List after operations: ";
        for (int val : lst) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        
        // Example of list merge
        sjtu::list<int> lst2;
        lst2.push_back(4);
        lst2.push_back(5);
        lst.merge(lst2);
        
        std::cout << "List after merge: ";
        for (int val : lst) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
}
