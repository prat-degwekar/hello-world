//
//To install mysql header files -> apt-get install libmysqlclient-dev
//To run embedded sql in c -> gcc "Embeddedsql Suppliers.c" `mysql_config --cflags --libs`

#include <mysql.h>
#include <string.h>
#include <stdio.h>

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

void select_all_from(char *table)
{
	char statement[512];
	snprintf(statement, 512, "SELECT * FROM %s", table);
	printf("The Result of \n%s;\n\n",statement);
	if (mysql_query(conn,statement)) 
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		
	}
	res = mysql_use_result(conn);
	//unsigned long *lengths;
	unsigned int num_fields;
	int i;
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		num_fields = mysql_num_fields(res);
		//lengths = mysql_fetch_lengths(res);
		for(i = 0; i < num_fields; i++)
		{
			printf("%s\t",row[i]);
		}
		printf("\n");
	}
	mysql_free_result(res);
	printf("\n");
}

void update_Supplier()
{
	int sno,status,old_sno;
	char sname[20],city[20];
	printf("\nEnter the Supplier number for whose record to update: ");
	scanf("%d",&old_sno);
	printf("\nEnter the new Supplier details:\n");
	printf("Supplier Number: ");
	scanf("%d",&sno);
	printf("Supplier Name: ");
	scanf("%s",sname);
	printf("Supplier Status: ");
	scanf("%d",&status);
	printf("Supplier City: ");
	scanf("%s",city);
	char statement[512];
	snprintf(statement,512,"UPDATE Supplier SET sno=%d,sname='%s',status=%d,city='%s' WHERE sno=%d",sno,sname,status,city,old_sno);
	printf("The Result of \n%s;\n\n",statement);
	if (mysql_query(conn,statement)) 
		fprintf(stderr, "%s\n", mysql_error(conn));
	else
		printf("\n\t\t Records updated successfully...\n");
}

void update_Part()
{
	int pno,weight,old_pno;
	char pname[30],color[20],city[20];
	printf("\nEnter the Part number for whose record to update: ");
	scanf("%d",&old_pno);
	printf("\nEnter the new Part details:\n");
	printf("Part Number: ");
	scanf("%d",&pno);
	printf("Part Name: ");
	scanf("%s",pname);
	printf("Part Colour: ");
	scanf("%s",color);
	printf("Part Weight: ");
	scanf("%d",&weight);
	printf("Part City: ");
	scanf("%s",city);
	char statement[512];
	snprintf(statement,512,"UPDATE Part SET pno=%d,pname='%s',color='%s',weight=%d,city='%s' WHERE pno=%d",pno,pname,color,weight,city,old_pno);
	printf("The Result of \n%s;\n\n",statement);
	if (mysql_query(conn,statement)) 
		fprintf(stderr, "%s\n", mysql_error(conn));
	else
		printf("\n\t\t Records updated successfully...\n");
}

void update_Project()
{
	int jno,old_jno;
	char jname[20],city[20];
	printf("\nEnter the Project number for whose record to update: ");
	scanf("%d",&old_jno);
	printf("\nEnter the new Project details:\n");
	printf("Project Number: ");
	scanf("%d",&jno);
	printf("Project Name: ");
	scanf("%s",jname);
	printf("Project City: ");
	scanf("%s",city);
	char statement[512];
	snprintf(statement,512,"UPDATE Project SET jno=%d,jname='%s',city='%s' WHERE jno=%d",jno,jname,city,old_jno);
	printf("The Result of \n%s;\n\n",statement);
	if (mysql_query(conn,statement)) 
		fprintf(stderr, "%s\n", mysql_error(conn));
	else
		printf("\n\t\t Records updated successfully...\n");
}

void update_Spj()
{
	int old_sno,old_pno,old_jno;
	int sno,pno,jno,qty;
	printf("\nEnter the Details of old record: ");
	printf("Old Supplier Number: ");
	scanf("%d",&old_sno);
	printf("Old Part Number: ");
	scanf("%d",&old_pno);
	printf("Old Project Number: ");
	scanf("%d",&old_jno);
	printf("\nEnter the new Transaction details:\n");
	printf("Supplier Number: ");
	scanf("%d",&sno);
	printf("Part Number: ");
	scanf("%d",&pno);
	printf("Project Number: ");
	scanf("%d",&jno);
	printf("Quantity: ");
	scanf("%d",&qty);
	char statement[512];
	snprintf(statement,512,"UPDATE Spj SET sno=%d,pno=%d,jno=%d,qty=%d WHERE sno=%d AND pno=%d AND jno=%d",sno,pno,jno,qty,old_sno,old_pno,old_jno);
	printf("The Result of \n%s;\n\n",statement);
	if (mysql_query(conn,statement)) 
		fprintf(stderr, "%s\n", mysql_error(conn));
	else
		printf("\n\t\t Records updated successfully...\n");
}

int main()
{
    char *server = "localhost"; // localhost for accessing local mysql
 	char *user = "root";// root for students
 	char *password = "qaz";/* set me first - pwd : iiitdm123 */ 
 	char *database = "Suppliers"; // Here you need to enter the database name if you have already other wise leave it free.

 	conn = mysql_init(NULL);
   /* Connect to database */
   if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
   {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   else printf("\nDatabase in Use: %s\n", database);

   int choice;
   do
   {
   		printf("\n Enter Choice for operation:\n");
   		printf("1.	Show entire table\n");
   		printf("2.	Search for something\n");
   		printf("3.	Update some record(s)\n");
   		printf("4.	Insert some new record(s)\n");
   		printf("5.	Delete some records(s)\n");
   		printf("6.	Enter Custom Query\n");
   		printf("7.	Disconnect\n");
   		printf("-----> ");
   		scanf("%d",&choice);
   		switch(choice)
   		{
   			case 1:printf("\t\t__SHOW ENTIRE TABLE MODULE__\n"); 				   
   				   int choice1;
   				   do
   				   {
   				   		printf("\nEnter choice to list the entire table for:\n1.	Suppliers\n2.	Parts\n3.	Projects\n4.	Spj Transactions\n5.	Back\n-----> ");
   				   		scanf("%d",&choice1);
   				   		switch(choice1)
   				  		{
   				   			case 1:select_all_from("Supplier");
   				   				   break;
   				   			case 2:select_all_from("Part");
   				   				   break;
   				   			case 3:select_all_from("Project");
   				   				   break;
   				   			case 4:select_all_from("Spj");
   				   				   break;
   				   			case 5:break;
   				   			default:printf("\n\tNo such table present!! Sorry!!\n");
   				   		}
   					}while(choice1!=5);
   				   break;
   			case 2:printf("\t\t__SEARCH MODULE__\n");
   				   int choice2,temp,trax1;
   				   char statement[512];
   				   do
   				   {
   				   		printf("\nEnter choice to search for:\n1.	All Parts supplied by a particular Supplier\n2.	All Projects where a particular Supplier supplies any part\n3.	All Projects where a particular Part is supplied\n4.	All parts supplied to a particular Project\n5.	The Part with the maximum requirement in the system\n6.	All parts of a given colour\n7.	Back\n-----> ");
   						scanf("%d",&choice2);
   						trax1=1;
   						switch(choice2)
   				   		{
   				   			case 1:printf("Enter the Supplier number:\t");
   				   				   scanf("%d",&temp);
   				   			   	   snprintf(statement,512,"SELECT * FROM Part WHERE pno IN (SELECT pno FROM Spj WHERE sno=%d)",temp);
   				   			   	   break;
   				   			case 2:printf("Enter the Supplier number:\t");
   				   				   scanf("%d",&temp);
   				   				   snprintf(statement,512,"SELECT * FROM Project WHERE jno IN (SELECT jno FROM Spj WHERE sno=%d)",temp);
   				   				   break;
   				   			case 3:printf("Enter the Part number:\t");
   				   				   scanf("%d",&temp);
   				   				   snprintf(statement,512,"SELECT * FROM Project WHERE jno IN (SELECT jno FROM Spj WHERE pno=%d)",temp);
   				   				   break;
   				   			case 4:printf("Enter the Project number:\t");
   				   				   scanf("%d",&temp);
   				   				   snprintf(statement,512,"SELECT * FROM Part WHERE pno IN (SELECT pno FROM Spj WHERE jno=%d)",temp);
   				   				   break;
   				   			case 5:snprintf(statement,512,"SELECT * FROM Part WHERE pno = (SELECT pno FROM Spj GROUP BY pno ORDER BY SUM(qty) DESC LIMIT 1)");
   				   				   break;
   				   			case 6:printf("Enter the colour in words:\t");
   				   				   char colour[10];
   				   				   scanf("%s",colour);
   				   				   snprintf(statement,512,"SELECT * FROM Part WHERE color = '%s'",colour);
   				   				   break;
   				   			case 7:trax1=0;
   				   				   break;
   				   			default:trax1=0;
   				   				   printf("\n\tNo such search option present!! Sorry!!\n");
   				   		}
   				   		if(trax1)
   				   		{
   				   			printf("The Result of \n%s;\n\n",statement);
							if (mysql_query(conn,statement)) 
							{
								fprintf(stderr, "%s\n", mysql_error(conn));
							}
							res = mysql_use_result(conn);
							//unsigned long *lengths;
							unsigned int num_fields;
							int i;
							while ((row = mysql_fetch_row(res)) != NULL)
							{
								num_fields = mysql_num_fields(res);
								//lengths = mysql_fetch_lengths(res);
								for(i = 0; i < num_fields; i++)
								{
									printf("%s\t",row[i]);
								}
								printf("\n");
							}
							mysql_free_result(res);
							printf("\n");
						}
					}while(choice2!=7);
   				   break;
   			case 3:printf("\t\t__UPDATE MODULE__\n");
   				   int choice3;
   				   do
   				   {
   				   		printf("\nEnter choice of Table to update record:\n1.	Supplier\n2.	Part\n3.	Project\n4.	Spj Transactions\n5.	Back\n-----> ");
   				   		scanf("%d",&choice3);
   				   		switch(choice3)
   				   		{
   							case 1:update_Supplier();
   				   				   break;
   				   			case 2:update_Part();
   				   				   break;
   				   			case 3:update_Project();
   				   				   break;
   				   			case 4:update_Spj();
   				   				   break;
   				   			case 5:break;
   				   			default:printf("\n\tNo such update option present!! Sorry!!\n");
   				   		}
   				   	}while(choice3!=5);
   				   break;
   			case 4:printf("\t\t__INSERT MODULE__\n");
   				   int choice4,trax4;
   				   char statement_4[512];
   				   do
   				   {
   				   		printf("\nEnter choice of Table to Insert record into:\n1.	Supplier\n2.	Part\n3.	Project\n4.	Spj Transactions\n5.	Back\n-----> ");
   				   		scanf("%d",&choice4);
   				   		trax4=1;
   				   		switch(choice4)
   				   		{
   							case 1:printf("\nEnter the new Supplier details:\n");
   								   int sno,status;
   								   char sname[20],city[20];
   								   printf("Supplier Number: ");
   								   scanf("%d",&sno);
   								   printf("Supplier Name: ");
   								   scanf("%s",sname);
   								   printf("Supplier Status: ");
   								   scanf("%d",&status);
   								   printf("Supplier City: ");
   								   scanf("%s",city);
   								   snprintf(statement_4,512,"INSERT INTO Supplier VALUES(%d,'%s',%d,'%s')",sno,sname,status,city);
   				   				   break;
   				   			case 2:printf("\nEnter the new Part details:\n");
   								   int pno,weight;
   								   char pname[30],color[20],pcity[20];
   								   printf("Part Number: ");
   								   scanf("%d",&pno);
   								   printf("Part Name: ");
   								   scanf("%s",pname);
   								   printf("Part Colour: ");
   								   scanf("%s",color);
   								   printf("Part Weight: ");
   								   scanf("%d",&weight);
   								   printf("Part City: ");
   								   scanf("%s",pcity);
   								   snprintf(statement_4,512,"INSERT INTO Part VALUES(%d,'%s','%s',%d,'%s')",pno,pname,color,weight,pcity);
   				   				   break;
   				   			case 3:printf("\nEnter the new Project details:\n");
   								   int jno;
   								   char jname[20],jcity[20];
   								   printf("Project Number: ");
   								   scanf("%d",&jno);
   								   printf("Project Name: ");
   								   scanf("%s",jname);
   								   printf("Project City: ");
   								   scanf("%s",jcity);
   								   snprintf(statement_4,512,"INSERT INTO Project VALUES(%d,'%s','%s')",jno,jname,jcity);
   				   				   break;
   				   			case 4:printf("\nEnter the new Transaction details:\n");
   								   int spj_jno,spj_sno,spj_pno,qty;
  								   printf("Supplier Number: ");
   								   scanf("%d",&spj_sno);
   								   printf("Part Number: ");
   								   scanf("%d",&spj_pno);
   								   printf("Project Number: ");
   								   scanf("%d",&spj_jno);
   								   printf("Quantity: ");
   								   scanf("%d",&qty);
   								   snprintf(statement_4,512,"INSERT INTO Spj VALUES(%d,%d,%d,%d)",spj_sno,spj_pno,spj_jno,qty);
   				   				   break;
   				   			case 5:trax4=0;
   				   				   break;
   				   			default:trax4=0;
   				   				    printf("\n\tNo such insert option present!! Sorry!!\n");
   				   		}
   				   		if(trax4)
   				   		{
   				   			printf("The Result of \n%s;\n\n",statement_4);
							if (mysql_query(conn,statement_4)) 
							{
								fprintf(stderr, "%s\n", mysql_error(conn));
							}
							else
								printf("\n\t\t 1 Record Inserted successfully...\n");
						}
   				   	}while(choice4!=5);
   				   break;
   			case 5:printf("\t\t__DELETE MODULE__\n");
   				   int choice5,trax5;
   				   char statement_5[512], condition[256];
   				   do
   				   {
   				   		printf("\nEnter choice of Table to Delete record from:\n1.	Supplier\n2.	Part\n3.	Project\n4.	Spj Transactions\n5.	Back\n-----> ");
   				   		scanf("%d",&choice5);
   				   		trax5=1;
   				   		char wait;
   				   		scanf("%c",&wait);
   				   		switch(choice5)
   				   		{
   							case 1:printf("\nEnter the condition (don't use where):\n");
   								   gets(condition);
   								   snprintf(statement_4,512,"DELETE FROM Supplier WHERE %s",condition);
   				   				   break;
   				   			case 2:printf("\nEnter the condition (don't use where):\n");
   								   gets(condition);
   								   snprintf(statement_4,512,"DELETE FROM Part WHERE %s",condition);
   				   				   break;
   				   			case 3:printf("\nEnter the condition (don't use where):\n");
   								   gets(condition);
   								   snprintf(statement_4,512,"DELETE FROM Project WHERE %s",condition);
   				   				   break;
   				   			case 4:printf("\nEnter the condition (don't use where):\n");
   								   gets(condition);
   								   snprintf(statement_4,512,"DELETE FROM Spj WHERE %s",condition);
   				   				   break;
   				   			case 5:trax5=0;
   				   				   break;
   				   			default:trax5=0;
   				   				    printf("\n\tNo such delete option present!! Sorry!!\n");
   				   		}
   				   		if(trax5)
   				   		{
   				   			printf("The Result of \n%s;\n\n",statement_4);
							if (mysql_query(conn,statement_4)) 
							{
								fprintf(stderr, "%s\n", mysql_error(conn));
							}
							else
								printf("\n\t\t 1 Record Deleted successfully...\n");
						}
   				   	}while(choice5!=5);
   				   break;
   			case 6:printf("\t\t__CUSTOM QUERY MODULE__\n");
   				   char statement_6[512];
   				   //scanf("%s",statement_6);
   				   char wait;
   				   scanf("%c",&wait);
   				   gets(statement_6);
   				   printf("The Result of \n%s;\n\n",statement_6);
				   if (mysql_query(conn,statement_6)) 
					{
						fprintf(stderr, "%s\n", mysql_error(conn));
					}
					else
						printf("\n\t\t Query syntactically correct...\n");
				   if(strncasecmp(statement_6,"SELECT",6)==0)
				   	{
				   		res = mysql_use_result(conn);
						//unsigned long *lengths;
						unsigned int num_fields;
						int i;
						while ((row = mysql_fetch_row(res)) != NULL)
						{
							num_fields = mysql_num_fields(res);
							//lengths = mysql_fetch_lengths(res);
							for(i = 0; i < num_fields; i++)
							{
								printf("%s\t",row[i]);
							}
							printf("\n");
						}
						mysql_free_result(res);
						printf("\n");
				   	}
				   break;
   			case 7:printf("\n\tVery Very Thanks for using my Program!!!\n\n");
   				   mysql_close(conn);
   				   break;
   			default:printf("\n\t\tInvalid Choice of Operation!!\n\n");
   		}
   }while(choice!=7);
   return 0;
}