```C

//信号量：袋子里的球 or 管理游泳池的手环
void P()
{
    WAIT_UNTIL(count > 0)
    {
        count--;
    }
}

void V()
{
    count++;
}

```