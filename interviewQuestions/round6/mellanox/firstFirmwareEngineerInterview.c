// 1. Implement a function to check whether a system (target) is big OR littel endian
// bool IsBigEndian();

// 2. Does an application is/should be aware of whether she runs on a big Vs. littele endian

// 3. a = 1
//    b = a << 3;
//    Does it matter if the target machine is big or littel 
//     ANSWER: Aside from networking "interoperability" between different archtiectures that requieres, for example, usage in the nthos() method, the application is UNAWARE 
//     of it.

// 4. Why there is a compilation error in the code below:
void question4()
{
  void* v_ptr;
  int a = 5;
  v_ptr = &a;
  *v_ptr = 6;
}

// 5. void question5()
{  
  

}

// 6. Are you familiar with any qualifiers in the C language
// ANSWER: auto, static, 

// 7. What is the difference between typedef and DEFINE

// 8. Why does printf show 16?
void question8()
{
    typedef struct dum 
    {
      double Time;
      unsigned char a;
    }a_t;

    int i;
     a_t d;
     i = sizeof(d);
     printf("%d\n", i);
}


// 9. Given a string and a char, duplicate all the occurences of the special string if/wehn applicable.
// For example: 
// string = sedfrt  and ch = d --> seddfr

int main(int argc, char** argv)
{
  const char funcName = "main - ";
  printf("%s start\n");
  printf("%s end\n");
}
}
