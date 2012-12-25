
namespace FreeQuant {

class FixMessageAugmentor {
public:
	Message newOrderSingleAugment(Message inMessage);

    /** Add the version-specific fields to a {@link quickfix.field.MsgType#EXECUTION_REPORT} message */
    public Message executionReportAugment(Message inMessage) throws FieldNotFound;

    /** Add the version-specific fields to a {@link quickfix.field.MsgType#ORDER_CANCEL_REJECT} message */
//    public Message cancelRejectAugment(Message inMessage);

    /** Add the version-specific fields to a {@link quickfix.field.MsgType#ORDER_CANCEL_REQUEST} message */
    public Message cancelRequestAugment(Message inMessage);

    /** Add the version-specific fields to a {@link quickfix.field.MsgType#ORDER_CANCEL_REPLACE_REQUEST} message */
    public Message cancelReplaceRequestAugment(Message inMessage);


    /** Determines whether or not we need to add a {@link quickfix.field.TransactTime} to a message */
    public boolean needsTransactTime(Message inMsg);
}
}
