function Byte* run_thread (procedure (*thread_function)(), Byte *arg)
{
	N_32 thread_id;

	CreateThread(0, 0, thread_function, arg, 0, &thread_id);

	return thread_id;
}


procedure sleep_thread (N_32 milliseconds)
{
	Sleep(milliseconds);
}
