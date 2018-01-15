procedure run_thread (procedure (*thread_function)(), Byte *arg)
{
	pthread_t thread;
    pthread_create(&thread, 0, thread_function, arg);
}


procedure sleep_thread (N_32 milliseconds)
{
	usleep(milliseconds*1000);
}
