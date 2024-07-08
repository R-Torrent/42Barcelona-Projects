This version of the project's header, intended for 42 Barcelona clusters with
its Macintosh machines, differs exclusively in the second argument of external
function 'gettimeofday':

struct timezone *tz -> void *tz
