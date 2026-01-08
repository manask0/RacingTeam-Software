Git - Free open source version control system.
## Common git commands
Clone - bring a repo hosted somewhere else (like github) into a folder on your local machine.
add - track files and changes in git
commit - save files in git
push - upload git commits to a remote repo like github
pull - opposite of push, download changes from a remote repo to your local machine
.git is a hidden folder that stores all files that save commits and file changes. it also has all of the changes made in the history of the repo 

git status - shows all files that were updated/ created / deleted but haven't been committed yet.

git push origin master - origin stands for location of git repo,  master is the branch we want to push to.

git init - when you created a folder on your local machine and want it to be on git, this initializes.
git commit -m "message"

git remote - remote (not on this computer). used to add reference  to github repo
git remote add origin https://github.com/user/reponame


<Github Workflow>
On github, by committing we add and commit at the same time (when it's our repo, we have full access to change whatever we want)
If we don't own the repo or need other people to review the code, we would need the extra step of creating a pull request.
</Github Workflow>

### Branching
When we create a new branch (let's say called feature), initially code on master and feature is same. But as we update feature, they are only seen on this branch. Each branch only keeps track of changes made on it. 

git checkout is used to switch between branches.
git checkout -b branchname - creates a new branch
git diff branchname - compares current branch with branchname
git merge branchname - merges changes from branchname into current branch
More common practice is to push changes on to github and then making a pr.


### Pull Request
A request to have your code pulled into another branch. (eg from feature branch to master branch). After making a PR, anyone can review and comment on our code. One PR is merge, we would delete the feature branch and switch back to main branch. 

git pull origin main - to get changes from github to local machine

git branch -d branchname deletes branchname


for files that are just modified (ie were committed earlier) we can add and commit at the same time using 
git commit -am "message"

### Undoing in git

git reset HEAD~1 (undo one commit)

git reset HASHKJNQJNJH
unstages all changes after commit with hash HASHKJNQJNJH (no longer saved with git, but still there in file)
git reset hard hash undoes any changes

