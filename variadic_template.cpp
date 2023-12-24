#include <iostream>

void 
print()
{
    std::cout << "I am called last and i am empty.\n";
}
 
template <typename T, typename... Types>
void 
print(T arg1, Types... arg2)
{
    std::cout << arg1 << std::endl;
 
    print(arg2...);
}
 
int main()
{
    print(1, 5020345, 0.5772156649,
          "I will print any and all arguments",
          "The defrosting has begun\n");
 
    return 0;
}