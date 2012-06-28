drop table t_giscup_edge;
drop table t_giscup_node;
drop table t_giscup_test_point_1;
drop table t_giscup_test_point_2;
drop table t_giscup_test_point_3;

create table t_giscup_node
(
    gid integer primary key,
    lat float not null, 
    lon float not null
);

select addgeometrycolumn('t_giscup_node','the_geom',4326,'POINT', 2);


create table t_giscup_edge
(
    gid integer primary key,
    start_node integer references t_giscup_node(gid) not null,
    end_node integer references t_giscup_node(gid) not null,    
    cost integer,
    length float,
    name varchar,
    type varchar
);

select addgeometrycolumn('t_giscup_edge','the_geom',4326,'LINESTRING', 2);


create table t_giscup_test_point_1
(
    gid serial primary key,
    edge integer
);
select addgeometrycolumn('t_giscup_test_point_1','the_geom',4326,'POINT', 2);


create table t_giscup_test_point_2
(
    gid serial primary key,
    edge integer
);
select addgeometrycolumn('t_giscup_test_point_2','the_geom',4326,'POINT', 2);


create table t_giscup_test_point_3
(
    gid serial primary key,
    edge integer
);
select addgeometrycolumn('t_giscup_test_point_3','the_geom',4326,'POINT', 2);

