int timerDelay(int lastTime, int t)
{
    while (ReadTimer1() - lastTime < t){}
    return ReadTimer1();
}

int main(void)
{
    TRISD = 0x0000;
    int lastTime = 0;
    const int array[8] = {
        0x0004, 0x0008, 0x0011, 0x0020, 0x0040, 0x0080, 0x0100, 0x0800};

    OpenTimer1(T1_ON | T1_SOURCE_INT | T2_32BIT_MODE_ON | T1_PS_1_256, 0xFFFF);

    while (1)
    {

        int j;
        for (j = 0; j < 8; j++)
        {
            LATD = array[j];
            lastTime = timerDelay(lastTime, 5000);
        }

        for (j = 6; j > 0; j--)
        {
            LATD = array[j];
            lastTime = timerDelay(lastTime, 5000);
        }
    }
    return 1;
}