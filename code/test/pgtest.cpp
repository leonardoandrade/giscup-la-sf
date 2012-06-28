#include <iostream>
#include <pqxx/pqxx>


int main()
{
    pqxx::connection c("dbname=giscup");
    pqxx::work txn(c);
    txn.exec("delete from t_giscup_node");
    txn.exec("insert into t_giscup_node(gid, lat, lon, the_geom) values(0, -47.4702757, -122.3366779,st_setsrid('POINT(47.4702757 -122.3366779)',4326))");
    txn.commit();
}

/*
int main(int, char *argv[])
{
  pqxx::connection c("dbname=company user=accounting");
  pqxx::work txn(c);

  pqxx::result r = txn.exec(
    "SELECT id "
    "FROM Employee "
    "WHERE name =" + txn.quote(argv[1]));

  if (r.size() != 1)
  {
    std::cerr
      << "Expected 1 employee with name " << argv[1] << ", "
      << "but found " << r.size() << std::endl;
    return 1;
  }

  int employee_id = r[0][0].as<int>();
  std::cout << "Updating employee #" << employee_id << std::endl;

  txn.exec(
    "UPDATE EMPLOYEE "
    "SET salary = salary + 1 "
    "WHERE id = " + txn.quote(employee_id));

  txn.commit();
}
*/
