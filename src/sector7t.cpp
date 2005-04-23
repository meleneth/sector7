#include"assert.h"

#include<string>


int main(char *argv[], int argc)
{
    std::string foo;

    foo = "Bar";

    assert(foo.length() ==3);

}
