class Stats
{
public:
    static float charToSpeed(char speed)
    {
        switch (speed)
        {
        case '0':
            return 0;
        case '1':
            return 0.1;
        case '2':
            return 0.2;
        case '3':
            return 0.3;
        case '4':
            return 0.4;
        case '5':
            return 0.5;
        case '6':
            return 0.6;
        case '7':
            return 0.7;
        case '8':
            return 0.8;
        case '9':
            return 0.9;
        case 'F':
            return 1;
        }
    }

    static float charToAngle(char angle)
    {
        switch (angle)
        {
        case 'J':
            return -1;
        case 'I':
            return -0.9;
        case 'H':
            return -0.8;
        case 'G':
            return -0.7;
        case 'F':
            return -0.6;
        case 'E':
            return -0.5;
        case 'D':
            return -0.4;
        case 'C':
            return -0.3;
        case 'B':
            return -0.2;
        case 'A':
            return -0.1;
        case 'S':
            return 0;
        case '0':
            return 0.1;
        case '1':
            return 0.2;
        case '2':
            return 0.3;
        case '3':
            return 0.4;
        case '4':
            return 0.5;
        case '5':
            return 0.6;
        case '6':
            return 0.7;
        case '7':
            return 0.8;
        case '8':
            return 0.9;
        case '9':
            return 1;
        }
    }

    static float speedTodirectionSpeed(char direction, float speed)
    {
        switch (direction)
        {
        case 'F':
            return speed;
        case 'B':
            return -speed;
        case 'D':
            return 0;
        }
    }
};