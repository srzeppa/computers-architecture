#include <stdio.h>

int main(){
    char *x = "aaa3 ab0     cccc2 c1 ";
    char bufor[100];

    asm volatile (
        ".intel_syntax noprefix;"
        "mov edx,%1;"           
        "mov ebx,%0;"            
        "mov esi,ebx;"         
        "mov edi,edx;"         
        "mov eax,esi;"
        
        "call zadanie1;"
        "jmp wyjscie2;"
        "zadanie1:"
        "push esi;"
        "push edi;"

        "pocoto:"

        "spacje:"
        "mov dh,[esi];"
        "cmp dh,0x20;"
        "jz ile_razy;"
        "mov dl,[esi];"
        "cmp dl,0;"
        "jz wyjscie;"
        "inc esi;"
        "jmp spacje;"

        "ile_razy:"
        "mov dl,[esi-1];"
        "sub dl, '0';"
        "ile_razy2:"
        "cmp dl,0;"
        "jz spacjokiler;"
        "dec dl;"
        "jmp wpisywanie;"

        "spacjokiler:"
        "mov dl,[esi];"
        "cmp dl,0;"
        "jz wyjscie;"
        "inc esi;"
        "cmp [esi], byte ptr 0x20;"
        "mov eax,esi;"
        "jnz pocoto;"
        "jmp spacjokiler;"

        "wpisywanie:"
		"cmp esi, eax;"
		"jz ile_razy2;"
        "mov cl,[eax];"
        "mov [edi],cl;"
        "inc eax;"
        "inc edi;"
        "jmp wpisywanie;"
         
        "wyjscie:"
        "pop edi;"
        "pop esi;"
        //"sub edi,edx;"
        "mov ecx,edi;" //adres
        "mov edx,11;" //edi;"  //dlugosc lancucha znakow
        "mov ebx,1;"  //numer deskryptora pliku do ktorego wyprowadzamy dane
        "mov eax,4;" //4 oznacza wywolanie
        "int 0x80;"  //przerwanie programowe
        
"ret;"
"wyjscie2:"
        ".att_syntax prefix;"
        :
        :"r"(x) , "r"(bufor)
        :"ebx","ecx","edx"

    );
    return 0;
}
