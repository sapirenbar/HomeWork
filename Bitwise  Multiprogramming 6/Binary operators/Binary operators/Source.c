 #include <stdio.h>
 #include <sys/types.h>
 main()
 {
	 int status;
	 pid_t pid1, pid2;
	 pid_t wait_pidA, wait_pidB;
	
		 if ((pid1 = fork()) == 0)
		 printf("first child context\n");
 else
		 if ((pid2 = fork()) == 0)
		 printf("second child context\n");
 else
		 {
		 wait_pidA = wait(&status);
		 if (wait_pidA == pid1)
		 printf("first child terminated\n");
		 if (wait_pidA == pid2)
			 printf("second child terminated\n");
		wait_pidB = wait(&status);
		 if (wait_pidB == pid1)
			 printf("first child terminated\n");
		 if (wait_pidB == pid2)
			 printf("second child terminated\n");
		 }
 }