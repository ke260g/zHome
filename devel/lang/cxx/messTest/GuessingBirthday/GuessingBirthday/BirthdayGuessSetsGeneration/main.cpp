#include<iostream>
#include<cstring>

#include"set/set.h"

/*
 * There are 5 sets of numbers, which are between 1 and 31;
 * These 5 sets are designed to implement such functionality:
 * The birthday is the sum of the first numbers in the sets where the day appears.
 * Each set includes 16 numbers.
 *
 * Here is the formula:
 * int SetFirstNum[5]; is an array for presenting the First Number in each sets,
 * bool Module[5]; is the modules for each FirstNumSets, either 1 or 0, but one member is 1 at least.
 *
 * int day = 0;
 * for(int i = 0; i < 5; i++)
 *     day += SetFirstNum[i] * Module[i];
 *
 * Given the SetFirstNum[i] value, different value for Module[i] makes the 'day' different;
 * There are (2**5 - 1) == 31 kinds of combination.
 */

int Ary[31], /* 1 to 31 */
    TmpAry[31], /* to store the temp value */
    TmpAry_counter,
    SetFirstNum[5],  /* first number in each set */
    Module[5];      /* modules */

Set ArySet;  /* 1 to 31 */
Set *TmpSet;

int IntMatch(const void *data1,
        const void *data2) {
    /*
     * if the data1 data2 are integer,
     * return 1 when they are equal
     * else return 0.
     */
    return (*(int *)data1 == *(int *)data2);
}

void IntDestroy(void *data) {
    free((int *)data);
}

bool ResCheck(void) {
    int i;  // common counter
    if(set_is_equal(&ArySet, TmpSet)) {
        putchar('#');
        for(i = 0; i < 5; i++)
            printf("%d\t", SetFirstNum[i]);
        putchar('\n');
        return 1;
    }
    else
        return 0;
}

int ModuleSum(void) {
    /* return the sum of current Module[5] */
    int res = 0;
    int i;
    for(i = 0; i < 5; i++)
        res += Module[i];
    return res;
}

void ModulesGen(const int pos) {
    /* Module[5]  value generation */
    if(pos < 4) {
        for(Module[pos] = 1; Module[pos] >= 0 && ModuleSum() > 0; Module[pos]--)
            ModulesGen(pos + 1);
        /* backward return */
        Module[pos] = 1;
    }
    else{ // pos == 4
        for(Module[pos] = 1; Module[pos] >= 0 && ModuleSum() > 0; Module[pos]--) {
            /* calculate the value */
            int i;

            /* record the value */
            for(i = 0; i < 5; i++)
                TmpAry[TmpAry_counter] += Module[i] * SetFirstNum[i];
            TmpAry_counter++;

        }
        /* backward return */
        Module[pos] = 1;
    }
}

int SetFirstNum_Sum(void) {
    /* return the sum of current SetFirstNum[5] */
    int sum = 0, /* result */
        i; /* common counter */

    for(i = 0; i < 5; i++)
        sum += SetFirstNum[i];

    return sum;
}

void SetFirstNumGen(const int pos) {
    /* SetFirstNum[5] value generation */
    if(pos < 4) {
        for(SetFirstNum[pos] = 1; SetFirstNum[pos] <= 27 && SetFirstNum_Sum() <= 31; SetFirstNum[pos]++)
            SetFirstNumGen(pos + 1);
        /* backward return */
        SetFirstNum[pos] = 1;
    }
    else { // pos == 4
        SetFirstNum[pos] = 31 - SetFirstNum_Sum() + SetFirstNum[4];

        int i;

#if 1   /* output implement */
        /* re-initialize TmpSet */
        TmpSet = (Set *)malloc(sizeof(Set));
        set_init(TmpSet, IntMatch, IntDestroy);

        /* initialize the TmpAry*/
        memset(TmpAry, 0, sizeof(int) * 31);
        TmpAry_counter = 0;

        /* initialize Module[5] */
        memset(Module, 1, sizeof(int) * 5);
        /* generate Module[5] */
        ModulesGen(0);

        /* insert the result into TmpSet */
        for(i = 0; i < 31; i++)
            set_insert(TmpSet, &TmpAry[i]);
        /* check the result */
        ResCheck();
        set_destroy(TmpSet);
#endif
        /* backward return */
        SetFirstNum[pos] = 1;
    }
}

int main(int argc, char **argv) {
    int i; /* common couter */

    /* initialize a array for 1 to 31*/
    set_init(&ArySet, IntMatch, IntDestroy);
    for(i = 0; i < 31; i++) {
        Ary[i] = i + 1;
        set_insert(&ArySet, &Ary[i]);
    }

    /* generate the SetFirstNum[5] */
    memset(SetFirstNum, 0, sizeof(int) * 5); /* initialize the SetFirstNum[5] */
    SetFirstNumGen(0); /* generate the SetFirstNum[5], core algorithm */

    set_destroy(&ArySet);
    set_destroy(TmpSet);
    return 0;
}
