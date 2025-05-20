FROM postgres

ADD db/* /docker-entrypoint-initdb.d/