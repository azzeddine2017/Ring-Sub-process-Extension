loadlib("ring_subprocess.dll")

Class ProcessManager {
    pObject
    
    func init
        pObject = subprocess_init()
    
    func runCommand command
        if not isnull(pObject) {
            return subprocess_create(pObject, command)
        }
        return 0
    
    func runCommandAsync command
        if not isnull(pObject) {
            return subprocess_execute(pObject, command)
        }
        return 0
    
    func waitForComplete
        if not isnull(pObject) {
            return subprocess_wait(pObject)
        }
        return 0
    
    func readOutput
        if not isnull(pObject) {
            return subprocess_getoutput(pObject)
        }
        return ""
    
    func kill
        if not isnull(pObject) {
            subprocess_terminate(pObject)
            pObject = NULL
        }
    
    func isActive
        if isnull(pObject) {
            return false
        }
        return true
}
