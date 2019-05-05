# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.Consumer.Debug:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/consumer/Debug/libConsumer.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/consumer/Debug/libConsumer.a


PostBuild.Error.Debug:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/error/Debug/libError.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/error/Debug/libError.a


PostBuild.Consumer.Release:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/consumer/Release/libConsumer.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/consumer/Release/libConsumer.a


PostBuild.Error.Release:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/error/Release/libError.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/error/Release/libError.a


PostBuild.Consumer.MinSizeRel:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/consumer/MinSizeRel/libConsumer.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/consumer/MinSizeRel/libConsumer.a


PostBuild.Error.MinSizeRel:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/error/MinSizeRel/libError.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/error/MinSizeRel/libError.a


PostBuild.Consumer.RelWithDebInfo:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/consumer/RelWithDebInfo/libConsumer.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/consumer/RelWithDebInfo/libConsumer.a


PostBuild.Error.RelWithDebInfo:
/Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/error/RelWithDebInfo/libError.a:
	/bin/rm -f /Users/bodie/meta/dev/workspace/workshop/dwarf-game/dwarf/dep/phoenix/xcode-build/src/error/RelWithDebInfo/libError.a




# For each target create a dummy ruleso the target does not have to exist
