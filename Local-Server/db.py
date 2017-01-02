import pymysql
import logging
import sys


class db(object):
    """docstring for db"""
    def __init__(self, host, user, db, passwd, supress=False):
        """
        start and test db connection
        """
        self.log = logging.getLogger()
        self.supress = supress
        try:
            self.conn = pymysql.connect(
                host=host,
                user=user,
                db=db,
                passwd=passwd
                )
            self.log.info("DB: Testing connection")
            self.test_connection()
        except Exception as e:
            self.log.critical("DB: Self test failed: {}".format(e))
            if not self.supress:
                sys.exit()
        self.log.info("DB: Test successful")

    def close(self):
        pass

    def write_ping(self, address, count, timestamp):
        """
        write a ping to the db
        """
        self.write(("INSERT INTO `api_ping` (`device_id`, `count`, "
                    "`time`) VALUES ('{}', {}, \'{}\')").
                   format(address, count, timestamp))

    def test_connection(self):
        """
        just do a show tables here
        """
        pass

    def read(self, query):
        self.log.debug("DB: " + query)
        cur = self.conn.cursor()
        cur.execute(query)
        return cur

    def write(self, query):
        self.log.debug("DB: " + query)
        cur = self.conn.cursor()
        cur.execute(query)
        self.conn.commit()
