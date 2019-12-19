# TODO:
#  1.	Combine the "user input" variable and the literal string to execute expected SQL behavior X
#  2.	Modify the user input variable to mimic a nefarious user injecting SQL into your application that causes your
#       SQL statement to return information it shouldn't X
#  3.	Change the method of forming SQL and show that it's not vulnerable to the same SQL Injection X
#  For extra credit, if you wish, you can:
#  •	Dynamically form the SQL statement based on user input X
#  •	Format the output of the SQL statement in a nicely formatted, table output
#  •	Develop a stored procedure in the db and call that stored procedure from your application.


import psycopg2 as p
import pandas as pd

def main():
   print("Welcome to HW6!")

   # Make a connection
   username = "f19wdb37"
   passwrd = "5m7rvG47!$xa"
   dataB = "f19wdb37"
   hostname = "dbclass.cs.pdx.edu"

   connection = p.connect(host=hostname, database=dataB, user=username, password=passwrd)

   db = connection.cursor()

   # Define your Query
#   query= "SELECT * FROM spy.Agent WHERE last LIKE'W%'" # Original statement
#   userin = "W%" # Hard coded user input for 1.
#   userin = "W"  # Hard coded user input for 1.
#   userin = "'or 1=1 --" # Input for 2. that shows there is a vulnerability to SQL injection using "'"
   # Source: http://initd.org/psycopg/docs/usage.html
#   userin = ("'or 1=1 --",) # Input for 3. showing that the vulnerability as been fixed using prepared statements.
#   userin = ("W%",) # Input for 3. showing that the statement still works with valid input (as in 1.) as expected.
#   userin = ("W",) # Input for 3. showing that the statement still works with valid input (as in 1.) as expected.
   userin = str(input("Search for last name (use % for wildcard): "))
   userin = (userin, )
#   print(userin) # DEBUG
#   print(type(userin)) # DEBUG

#   query= "SELECT * FROM spy.Agent WHERE last LIKE\'" + userin + "\'" # SQL statement for 1. and 2.
#   query = "SELECT * FROM spy.Agent WHERE last LIKE %s" # SQL statment for 3.
   query = "SELECT * FROM spy.Agent WHERE last LIKE %s" # SQL statment for 3.
#   query = "SELECT * FROM spy.Agent WHERE last = %s" # SQL statment for 3.
#   print(query) # DEBUG

   # Execute your Query
#   db.execute(query) # Execution for 1 and 2
   db.execute(query, userin) # Execution for 3

   # do stuff with the returned data....

   # rows and columns/fields returned
   col_names = [desc[0] for desc in db.description]

   # fetch all the rows from the db
   rows = db.fetchall()
#   print(col_names)

   #look at the rows, one-by-one\
#   for row in rows:
#      print(row)

   # Source: https://stackoverflow.com/questions/46777397/how-can-i-see-the-output-in-python-as-like-sql-table-format
   print(pd.DataFrame(rows, columns=col_names))

   #close the connectiondb.close()
   connection.close()

main()