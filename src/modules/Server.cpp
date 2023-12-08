class CarServer
{
private:
    char *stats;
    char *lastStats;
    int statLength;

public:
    CarServer()
        : statLength(0)
    {
    }

    CarServer(int statLength)
        : statLength(statLength)
    {
        stats = new char[statLength];
        lastStats = new char[statLength];
        clearStats();
    }

    void clearStats()
    {
        for (int i = 0; i < statLength; i++)
        {
            stats[i] = '0';
        }
    }

    bool checkForUpdates()
    {
        bool updated = false;

        for (int i = 0; i < statLength; i++)
        {
            if (stats[i] != lastStats[i])
            {
                updated = true;
                break;
            }
        }

        if (updated)
        {
            lastStats = stats;
        }

        return updated;
    }

    char getStat(int index)
    {
        return stats[index];
    }

    void setStat(int index, char value)
    {
        stats[index] = value;
    }

    int getStatLength()
    {
        return statLength;
    }

    char *getStatString()
    {
        char *status = new char[statLength];
        for (int i = 0; i < statLength; i++)
        {
            status[i] = stats[i];
        }

        return status;
    }
};