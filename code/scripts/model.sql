--drop table t_giscup_edge;
drop table t_giscup_track_point_1;
drop table t_giscup_track_point_2;
drop table t_giscup_track_point_3;
drop table t_giscup_track_point_4;
drop table t_giscup_track_point_5;
drop table t_giscup_track_point_6;
drop table t_giscup_track_point_7;
drop table t_giscup_track_point_8;
drop table t_giscup_track_point_9;
drop table t_giscup_track_point_10;


create table t_giscup_edge
(
    gid serial primary key,
    id integer,
    --start_node integer references t_giscup_node(gid) not null,
    --end_node integer references t_giscup_node(gid) not null,    
    cost integer,
    length float,
    name varchar,
    type varchar
);

select addgeometrycolumn('t_giscup_edge','the_geom',900913,'LINESTRING', 2);


create table t_giscup_track_point_1
(
    gid serial primary key,
    id integer unique not null,
    edge integer,
    confidence float,
    comments varchar,
    correct boolean,
    speed float
);
select addgeometrycolumn('t_giscup_track_point_1','the_geom',900913,'POINT', 2);


create table t_giscup_track_point_2
(
    gid serial primary key,
    id integer unique not null,
    edge integer,
    confidence float,
    comments varchar,
    correct boolean,
    speed float
);
select addgeometrycolumn('t_giscup_track_point_2','the_geom',900913,'POINT', 2);


create table t_giscup_track_point_3
(
    gid serial primary key,
    id integer unique not null,
    edge integer,
    confidence float,
    comments varchar,
    correct boolean,
    speed float
);
select addgeometrycolumn('t_giscup_track_point_3','the_geom',900913,'POINT', 2);

create table t_giscup_track_point_4
(
    gid serial primary key,
    id integer unique not null,
    edge integer,
    confidence float,
    comments varchar,
    correct boolean,
    speed float
);
select addgeometrycolumn('t_giscup_track_point_4','the_geom',900913,'POINT', 2);

create table t_giscup_track_point_5
(
    gid serial primary key,
    id integer unique not null,
    edge integer,
    confidence float,
    comments varchar,
    correct boolean,
    speed float
);
select addgeometrycolumn('t_giscup_track_point_5','the_geom',900913,'POINT', 2);

create table t_giscup_track_point_6
(
    gid serial primary key,
    id integer unique not null,
    edge integer,
    confidence float,
    comments varchar,
    correct boolean,
    speed float
);
select addgeometrycolumn('t_giscup_track_point_6','the_geom',900913,'POINT', 2);

create table t_giscup_track_point_7
(
    gid serial primary key,
    id integer unique not null,
    edge integer,
    confidence float,
    comments varchar,
    correct boolean,
    speed float
);
select addgeometrycolumn('t_giscup_track_point_7','the_geom',900913,'POINT', 2);

create table t_giscup_track_point_8
(
    gid serial primary key,
    id integer unique not null,
    edge integer,
    confidence float,
    comments varchar,
    correct boolean,
    speed float
);
select addgeometrycolumn('t_giscup_track_point_8','the_geom',900913,'POINT', 2);

create table t_giscup_track_point_9
(
    gid serial primary key,
    id integer unique not null,
    edge integer,
    confidence float,
    comments varchar,
    correct boolean,
    speed float
);
select addgeometrycolumn('t_giscup_track_point_9','the_geom',900913,'POINT', 2);

create table t_giscup_track_point_10
(
    gid serial primary key,
    id integer unique not null,
    edge integer,
    confidence float,
    comments varchar,
    correct boolean,
    speed float
);
select addgeometrycolumn('t_giscup_track_point_10','the_geom',900913,'POINT', 2);


--indexes
create index idx_t_giscup_edge_the_geom on t_giscup_edge using gist(the_geom);
create index idx_t_giscup_track_point_1_id on t_giscup_track_point_1(id);
create index idx_t_giscup_track_point_2_id on t_giscup_track_point_2(id);
create index idx_t_giscup_track_point_3_id on t_giscup_track_point_3(id);
create index idx_t_giscup_track_point_4_id on t_giscup_track_point_4(id);
create index idx_t_giscup_track_point_5_id on t_giscup_track_point_5(id);
create index idx_t_giscup_track_point_6_id on t_giscup_track_point_6(id);
create index idx_t_giscup_track_point_7_id on t_giscup_track_point_7(id);
create index idx_t_giscup_track_point_8_id on t_giscup_track_point_8(id);
create index idx_t_giscup_track_point_9_id on t_giscup_track_point_9(id);
create index idx_t_giscup_track_point_10_id on t_giscup_track_point_10(id);




