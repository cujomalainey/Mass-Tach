
class web():
    """docstring for web"""
    def __init__(self, mgr):
        self.mgr = mgr
        self.routes = {
            "/": self.status,
            "/shutdown/": self.shutdown
        }

    def register(self, app):
        for route in self.routes:
            app.add_url_rule(route, view_func=self.routes[route])

    def status(self):
        return('Hello, World!')

    def shutdown(self):
        func = request.environ.get('werkzeug.server.shutdown')
        if func is None:
            raise RuntimeError('Not running with the Werkzeug Server')
        func()
