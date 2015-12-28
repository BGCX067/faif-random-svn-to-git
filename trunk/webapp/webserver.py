
from os import curdir, sep, path
from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import json
import urlparse
from n_puzzle import *

result_counter = 0

class PuzzleServHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        try:
            if self.path.endswith("/"):
                f = open(curdir + sep + '/html/' + "index.html")
                self.send_response(200)
                self.send_header('Content-type',	'text/html')
                self.end_headers()
                self.wfile.write(f.read())
                f.close()
                return

            if  self.path.endswith(".js"):
                filename = ""
                if self.path.endswith("jquery.js"):
                    filename = "jquery.js"
                elif self.path.endswith("jquery.jqpuzzle.js"):
                    filename = "jquery.jqpuzzle.js"
                print filename
                f = open(curdir + sep + '/javascript/' + filename)                self.send_response(200)
                self.send_header('Content-type',	'text/javascript')
                self.end_headers()
                self.wfile.write(f.read())

                f.close()
                return

            if self.path.endswith(".css"):
                f = open(curdir + sep + '/css/jquery.jqpuzzle.css')                self.send_response(200)
                self.send_header('Content-type',	'text/css')
                self.end_headers()
                self.wfile.write(f.read())
                f.close()
                return


            if self.path.endswith(".txt"):
                f = open(curdir + sep + '/results/' + self.path)     #potential security hole
                self.send_response(200)
                self.send_header('Content-type',	'text/html')
                self.end_headers()
                self.wfile.write(f.read())
                f.close()
                return


            if self.path.find("query") > -1:
                self.send_response(200)
                (scm, netloc, path, params, query, fragment) = urlparse.urlparse(self.path, 'http')
                (puzzle_size,puzzle_arr) = self.parsePuzzleSetQuery(query)
                puzzle = n_puzzle()
                v_puzzle_arr = vector_int()
                result = vector_int()
                v_puzzle_arr[:] = puzzle_arr

                global result_counter
                result_counter = result_counter + 1

                result_filename = "out%d.txt"%(result_counter)    
                result_len = puzzle.compute(puzzle_size, v_puzzle_arr, result_filename)
                if result_len > 5*10**5:
                    result_filename = "plik_zbyt_duzy.txt"

                self.send_header('Content-type',	'text/html')
                self.end_headers()
#                response=json.dumps(result, cls=VectorIntEncoder)

                response=json.dumps({'result_len': result_len, 'result_fname': result_filename})

                self.wfile.write(response) 
                return
                
            if self.path.endswith(".png"):
                f = open(curdir + sep + '/images/' +self.path)
                self.send_response(200)
                self.send_header('Content-type',	'image/png')
                self.end_headers()
                self.wfile.write(f.read())
                return
                
            return

        except IOError:
            self.send_error(404,'File Not Found: %s' % self.path)

    def parsePuzzleSetQuery(self,qs):
        """ """
        parseq_query = urlparse.parse_qs(qs)
        puzzle_size = 0
        puzzle_arr = []
#        algorithms = {'random_walk': solution_alg.random_walk, 'random_sampling': solution_alg.random_sampling}
#        algorithm = ''

        try:
#            alg_selection = parseq_query['algorithm'][0]
#            algorithm = algorithms[alg_selection]
            puzzle_size = int(parseq_query['size'][0])
            x=parseq_query['x']
            for i in xrange(0,len(x)):
               puzzle_arr.append(int(x[i]))
        except KeyError:
            print "Bad request"

        return (puzzle_size,puzzle_arr)


def main():
    try:
        server = HTTPServer(('', 8080), PuzzleServHandler)
        print 'started httpserver...'
        server.serve_forever()
    except KeyboardInterrupt:
        print '^C received, shutting down server'
        server.socket.close()

if __name__ == '__main__':
    main()

