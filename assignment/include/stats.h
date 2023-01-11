#pragma once

// int test_set[] = {21, 38, 12, 41};
// double var = compute_variance(test_set, 4);
// printf("%f\n", var);

double compute_mean(int *data, int data_length)
{
    double sum = 0;
    for (int i = 0; i < data_length; i++)
    {
        sum += data[i];
    }
    double mean = sum / data_length;
    return mean;
}

double compute_variance(int *data, int data_length)
{
    double mean = compute_mean(data, data_length);
    double sum_squared_dist = 0;
    for (int i = 0; i < data_length; i++)
    {
        double distance = data[i] - mean;
        sum_squared_dist += distance * distance;
    }
    double variance = sum_squared_dist / data_length;
    return variance;
}

int compute_min(int *data, int data_length)
{
    int current_min = data[0];
    for (int i = 0; i < data_length; i++)
    {
        if (data[i] < current_min)
        {
            current_min = data[i];
        }
    }
    return current_min;
}

int compute_max(int *data, int data_length)
{
    int current_max = data[0];
    for (int i = 0; i < data_length; i++)
    {
        if (data[i] < current_max)
        {
            current_max = data[i];
        }
    }
    return current_max;
}
