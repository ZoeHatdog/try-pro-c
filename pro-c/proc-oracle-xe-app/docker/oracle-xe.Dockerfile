FROM oracle/database:18.4.0-xe

ENV ORACLE_HOME=/opt/oracle/product/18c/dbhomeXE
ENV ORACLE_SID=XE
ENV ORACLE_PWD=oracle

EXPOSE 1521 5500

VOLUME ["/opt/oracle/oradata"]

COPY setup_db.sh /opt/oracle/setup_db.sh
RUN chmod +x /opt/oracle/setup_db.sh

CMD ["/opt/oracle/setup_db.sh"]