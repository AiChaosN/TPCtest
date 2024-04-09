CREATE TABLE CUSTOMER
(
    C_CUSTKEY     INT NOT NULL,
    C_NAME        VARCHAR(25) NOT NULL,
    C_ADDRESS     VARCHAR(40) NOT NULL,
    C_NATIONKEY   INT NOT NULL,
    C_PHONE       CHAR(15) NOT NULL,
    C_ACCTBAL     FLOAT NOT NULL,
    C_MKTSEGMENT  CHAR(10) NOT NULL,
    C_COMMENT     VARCHAR(117) NOT NULL,
    PRIMARY KEY (C_CUSTKEY)
);

CREATE TABLE LINEITEM
(
    L_ORDERKEY       INT NOT NULL,
    L_PARTKEY        INT NOT NULL,
    L_SUPPKEY        INT NOT NULL,
    L_LINENUMBER     INT NOT NULL,
    L_QUANTITY       FLOAT NOT NULL,
    L_EXTENDEDPRICE  FLOAT NOT NULL,
    L_DISCOUNT       FLOAT NOT NULL,
    L_TAX            FLOAT NOT NULL,
    L_RETURNFLAG     CHAR(1) NOT NULL,
    L_LINESTATUS     CHAR(1) NOT NULL,
    L_SHIPDATE       DATE NOT NULL,
    L_COMMITDATE     DATE NOT NULL,
    L_RECEIPTDATE    DATE NOT NULL,
    L_SHIPINSTRUCT   CHAR(25) NOT NULL,
    L_SHIPMODE       CHAR(10) NOT NULL,
    L_COMMENT        VARCHAR(44) NOT NULL,
    PRIMARY KEY (L_ORDERKEY, L_LINENUMBER)
);

CREATE TABLE NATION
(
    N_NATIONKEY   INT NOT NULL,
    N_NAME        CHAR(25) NOT NULL,
    N_REGIONKEY   INT NOT NULL,
    N_COMMENT     VARCHAR(152) NOT NULL,
    PRIMARY KEY (N_NATIONKEY)
);

CREATE TABLE ORDERS
(
    O_ORDERKEY        INT NOT NULL,
    O_CUSTKEY         INT NOT NULL,
    O_ORDERSTATUS     CHAR(1) NOT NULL,
    O_TOTALPRICE      FLOAT NOT NULL,
    O_ORDERDATE       DATE NOT NULL,
    O_ORDERPRIORITY   CHAR(15) NOT NULL,
    O_CLERK           CHAR(15) NOT NULL,
    O_SHIPPRIORITY    INTEGER NOT NULL,
    O_COMMENT         VARCHAR(79) NOT NULL,
    PRIMARY KEY (O_ORDERKEY)
);

CREATE TABLE PART
(
    P_PARTKEY      INT NOT NULL,
    P_NAME         VARCHAR(55) NOT NULL,
    P_MFGR         CHAR(25) NOT NULL,
    P_BRAND        CHAR(10) NOT NULL,
    P_TYPE         VARCHAR(25) NOT NULL,
    P_SIZE         INT NOT NULL,
    P_CONTAINER    CHAR(10) NOT NULL,
    P_RETAILPRICE  FLOAT NOT NULL,
    P_COMMENT      VARCHAR(23) NOT NULL,
    PRIMARY KEY (P_PARTKEY)
);

CREATE TABLE PARTSUPP
(
    PS_PARTKEY     INT NOT NULL,
    PS_SUPPKEY     INT NOT NULL,
    PS_AVAILQTY    INT NOT NULL,
    PS_SUPPLYCOST  FLOAT NOT NULL,
    PS_COMMENT     VARCHAR(199) NOT NULL,
    PRIMARY KEY (PS_PARTKEY, PS_SUPPKEY)
);

CREATE TABLE REGION
(
    R_REGIONKEY   INT NOT NULL,
    R_NAME        CHAR(25) NOT NULL,
    R_COMMENT     VARCHAR(152) NOT NULL,
    PRIMARY KEY (R_REGIONKEY)
);

CREATE TABLE SUPPLIER
(
    S_SUPPKEY    INT NOT NULL,
    S_NAME       CHAR(25) NOT NULL,
    S_ADDRESS    VARCHAR(40) NOT NULL,
    S_NATIONKEY  INT NOT NULL,
    S_PHONE      CHAR(15) NOT NULL,
    S_ACCTBAL    FLOAT NOT NULL,
    S_COMMENT    VARCHAR(101) NOT NULL,
    PRIMARY KEY (S_SUPPKEY)
);
